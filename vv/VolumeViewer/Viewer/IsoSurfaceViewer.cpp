/********************************************************************
	created:	21:11:2011   9:49
	filename: 	C:\Users\jim\Documents\programming\VTK\bdvd\vv\VolumeViewer\Viewer\IsoSurfaceViewer.cpp
	author:		Jim Pelton
	
	purpose:	
*********************************************************************/


#include "IsoSurfaceViewer.h"


IsoSurfaceViewer::IsoSurfaceViewer(void){}


IsoSurfaceViewer::IsoSurfaceViewer(DataReaderFormat & drf, int screenwidth, int screenheight,
    int iso_val, int algorithm) : 
    Viewer(drf,  screenwidth,  screenheight)
{
    m_iso_value = iso_val;
    m_algorithm = algorithm;
}


IsoSurfaceViewer::~IsoSurfaceViewer(void)
{}

/*
 *	Setup the vtk pipeline, the marching cubes extractor, etc.
 */
int IsoSurfaceViewer::Setup()
{
    fprintf(stdout, "Setup...\n");
    polyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    if (m_readerFormat.readerType == VV_POLY_DATA_READER )
    {
        vtkPolyDataReader *vpdr = vtkPolyDataReader::New();
        vpdr->SetFileName(m_readerFormat.fileName);        
        polyDataMapper->SetInput(vpdr->GetOutput());
    }
    else{
        reader = vtkSmartPointer<vtkBMPReader>::New();
        reader->SetFilePrefix(m_readerFormat.filePrefix);
        reader->SetAllow8BitBMP(m_readerFormat.is8Bit);

        reader->SetFileNameSliceOffset( m_readerFormat.imgRngStart );
        reader->SetDataExtent( 0, m_readerFormat.dimX,
            0, m_readerFormat.dimY,
            m_readerFormat.imgRngStart,
            m_readerFormat.imgRngEnd);

        /*reader->SetDataSpacing(m_readerFormat.nSpacingX,
        m_readerFormat.nSpacingY,
        m_readerFormat.nSpacingZ);*/

        reader->SetDataOrigin(0.,0.,0.);
        reader->SetDataScalarTypeToUnsignedChar();
        reader->SetDataByteOrderToBigEndian();

        extractor = vtkSmartPointer<vtkMarchingCubes>::New();
        vtkMarchingCubes *pMCubes = vtkMarchingCubes::SafeDownCast(extractor);
        pMCubes->SetInputConnection(reader->GetOutputPort());
        pMCubes->ComputeNormalsOn();
        pMCubes->SetValue(0, 80);  
    
        polyDataMapper->SetInputConnection(extractor->GetOutputPort());
    }
    
    polyDataMapper->ScalarVisibilityOff();
    polyDataMapper->Update();

    surface = vtkSmartPointer<vtkLODActor>::New();
    surface->SetMapper(polyDataMapper);
    vtkLODActor::SafeDownCast(surface)->SetNumberOfCloudPoints(100000);
    surface->GetProperty()->SetColor(0.4,0.3,0.3);
    surface->GetProperty()->SetOpacity(0.3);

    m_surfaceColor[0] = m_surfaceColor[1] = m_surfaceColor[2] = 1.f;

    return 1;
}

/*
 *	Get the appropriate filter to put between polydatamapper 
 *  and whatever is before it.
 */
vtkAlgorithmOutput *IsoSurfaceViewer::getAlgoOutput()
{
    switch(m_algorithm)
    {
    case CON_FILTER:
        conFilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
        conFilter->SetInputConnection(appendFilter->GetOutputPort());
        conFilter->SetExtractionModeToAllRegions();
        conFilter->ColorRegionsOn();
        conFilter->Update();
        return conFilter->GetOutputPort();
    default:
        return appendFilter->GetOutputPort();
    } 
}

/*
 *	Make everything ready to render. Adds actor to the renderer,
 *  sets up the camera, update rate, camera position.
 *  Does nothing to read data. 
 *  To set up the pipeline call Setup() before InitializeRenderer().
 */
void IsoSurfaceViewer::InitializeRenderer()
{

    fprintf(stdout, "Init renderer...\n");

    m_ren->AddActor(surface);

    double *c = surface->GetCenter();
    m_camera->SetFocalPoint(0.,0.,0.);
    m_camera->SetPosition(c[0] + 900, c[1], c[2]);

    m_camera->SetViewUp(0, 0, 1);
    m_camera->ComputeViewPlaneNormal();
    m_ren->ResetCamera();
    m_camera->Dolly(1.5);

    m_ren->SetBackground(.1,0.1,0.1);
    m_renWin->SetSize(ScreenWidth(), ScreenHeight());

    m_ren->ResetCameraClippingRange();


    m_iren->SetDesiredUpdateRate(10.0);

    m_iren->Initialize();
}

vtkPolyData* IsoSurfaceViewer::GetPolyData()
{
	vtkMarchingCubes *pMC = vtkMarchingCubes::SafeDownCast(extractor);
	return pMC->GetOutput();
}

/************************************************************************/
/* getters/setters                                                      */
/************************************************************************/
int IsoSurfaceViewer::IsoValue() const
{
    return m_iso_value;
}


void IsoSurfaceViewer::IsoValue( int val )
{
    m_iso_value = val;
    vtkMarchingCubes::SafeDownCast(extractor)->SetValue(0, val);
}

vtkSmartPointer<vtkLODActor> IsoSurfaceViewer::Surface() const
{
    return surface;
}

void IsoSurfaceViewer::Surface( vtkSmartPointer<vtkLODActor> val )
{
    surface = val;
}

void IsoSurfaceViewer::SetColorRed(double red)
{
    m_surfaceColor[0] = red;
    surface->GetProperty()->SetColor(m_surfaceColor);
}

void IsoSurfaceViewer::SetColorGreen(double green)
{
    m_surfaceColor[1] = green;
    surface->GetProperty()->SetColor(m_surfaceColor);
}

void IsoSurfaceViewer::SetColorBlue(double blue)
{
    m_surfaceColor[2] = blue;
    surface->GetProperty()->SetColor(m_surfaceColor);
}

void IsoSurfaceViewer::SetColorRGB(double * rgb)
{
    m_surfaceColor[0] = rgb[0];
    m_surfaceColor[1] = rgb[1];
    m_surfaceColor[2] = rgb[2];
    surface->GetProperty()->SetColor(m_surfaceColor);
}

int IsoSurfaceViewer::Algorithm() const
{
    return m_algorithm;
}

void IsoSurfaceViewer::Algorithm( int val )
{
    m_algorithm = val;
}

