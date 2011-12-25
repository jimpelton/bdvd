/********************************************************************
	created:	21:11:2011   9:49
	filename: 	C:\Users\jim\Documents\programming\VTK\bdvd\vv\VolumeViewer\Viewer\IsoSurfaceViewer.cpp
	author:		Jim Pelton
	
	purpose:	
*********************************************************************/


#include "IsoSurfaceViewer.h"

#define SETUP_SUCCESS 0
#define SETUP_FAILURE !SETUP_SUCCESS

IsoSurfaceViewer::IsoSurfaceViewer(void){}


IsoSurfaceViewer::IsoSurfaceViewer(DataReaderFormat & drf, int screenwidth, int screenheight,
    int iso_val, int algorithm) : 
    Viewer(drf,  screenwidth,  screenheight)
{
    m_iso_value = iso_val;
    m_algorithm = algorithm;
    m_surfaceColor[0] = m_surfaceColor[1] = m_surfaceColor[2] = m_surfaceColor[3] = 1.0;
    m_rotXYZ[0] = m_rotXYZ[1] = m_rotXYZ[2] = 0.0;
}


IsoSurfaceViewer::~IsoSurfaceViewer(void)
{}

/*
 *  Setup the vtk pipeline, the marching cubes extractor, etc.
 *  Chooses the correct reader from the DataReaderFormat.
 */
int IsoSurfaceViewer::Setup()
{
    fprintf(stdout, "Setup...\n");
    polyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    reader = ReaderFactory::GetReader(&m_readerFormat);


    if (m_readerFormat.readerType == VV_POLY_DATA_READER )
    {
        polyDataMapper->SetInputConnection(reader->GetOutputPort());
        //polyData = polyDataMapper->GetInput();
    }
    else
    {
        extractor = vtkSmartPointer<vtkMarchingCubes>::New();
        vtkMarchingCubes *pMCubes = vtkMarchingCubes::SafeDownCast(extractor);
        pMCubes->SetInputConnection(reader->GetOutputPort());
        pMCubes->ComputeNormalsOn();
        pMCubes->SetValue(0, m_iso_value); 
        pMCubes->Update();
        //polyData = pMCubes->GetOutput();
        polyDataMapper->SetInputConnection(extractor->GetOutputPort());
    }
    
    polyDataMapper->ScalarVisibilityOff();
    polyDataMapper->Update();
    polyData = polyDataMapper->GetInput();

    surface = vtkSmartPointer<vtkLODActor>::New();
    surface->SetMapper(polyDataMapper);
    vtkLODActor::SafeDownCast(surface)->SetNumberOfCloudPoints(100000);
    surface->GetProperty()->SetColor(m_surfaceColor[0], m_surfaceColor[1], m_surfaceColor[2]);
    surface->GetProperty()->SetOpacity(m_surfaceColor[3]);
    surface->RotateX(m_rotXYZ[0]);
    surface->RotateY(m_rotXYZ[1]);
    surface->RotateZ(m_rotXYZ[2]);

    return SETUP_SUCCESS;
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
 *  To set up the pipeline call IsoSurfaceViewer::Setup() before InitializeRenderer().
 */
void IsoSurfaceViewer::InitializeRenderer()
{

    fprintf(stdout, "Init renderer...\n");

    cubeAxes = vtkSmartPointer<vtkCubeAxesActor>::New();
    cubeAxes->SetBounds(polyDataMapper->GetBounds());
    cubeAxes->SetCamera(m_ren->GetActiveCamera());
    cubeAxes->VisibilityOn();
    cubeAxes->SetFlyModeToStaticTriad();
    cubeAxes->SetLabelScaling(true, 0.5, 0.5, 0.5);


    m_ren->AddActor(cubeAxes);
    m_ren->AddActor(surface);
    m_ren->ResetCamera();

    double *c = surface->GetCenter();
    m_camera->SetFocalPoint(0.,0.,0.);
    m_camera->SetPosition(c[0] + 900, c[1], c[2]);

    m_camera->SetViewUp(0, 0, 1);
    //m_camera->SetViewUp(surface->GetOrientation());
    m_camera->ComputeViewPlaneNormal();
    m_ren->ResetCamera();
    m_camera->Dolly(1.5);

    m_ren->SetBackground(0.1,0.1,0.1);
    m_renWin->SetSize(ScreenWidth(), ScreenHeight());

    m_ren->ResetCameraClippingRange();
    

    fprintf(stdout, "Done initializing render...\n");
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

vtkPolyData* IsoSurfaceViewer::GetPolyData()
{
	return polyData;
}


//set the rotation values for the surface. rotates about
//the actor's xyz coordinate axis, not the world.
//you must update the renderer after this call.
void IsoSurfaceViewer::SetRotate(double *xyz)
{
	m_rotXYZ[0] = xyz[0];
	m_rotXYZ[1] = xyz[1];
	m_rotXYZ[2] = xyz[2];
}

//get the rotation values for the surface.
//Returns an array of 3 doubles.
double *IsoSurfaceViewer::GetRotate()
{
	return m_rotXYZ;
}
