

#include "VolumeViewer.h"
#include <vtkBMPReader.h>
#include <vtkVolumeRayCastCompositeFunction.h>
using std::string;

VolumeViewer::VolumeViewer(void) : Viewer()
{
	assignDefaults();
}

VolumeViewer::VolumeViewer(DataReaderFormat	& drf, int screenwidth, int screenheight) : 
	Viewer(drf, screenwidth, screenheight)
{
	assignDefaults();
}

VolumeViewer::~VolumeViewer()
{	
	//nothing...can you believe it?!?
}

void VolumeViewer::assignDefaults()
{
	volumeColorTransfer = NULL;
	volumeScalarTransfer = NULL;
	volumeGradTransfer = NULL;

	m_keypressStyle = new KeypressInteractorStyle();
	m_keypressStyle->SetVolumeViewer(this);
}


int VolumeViewer::Setup()
{

	m_keypressStyle->SetCurrentRenderer(m_ren);

	volume = vtkSmartPointer<vtkVolume>::New();
	
	volumeMapper = vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	vRayCastFunction = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
	vtkVolumeRayCastMapper *p = vtkVolumeRayCastMapper::SafeDownCast(volumeMapper);
	p->SetVolumeRayCastFunction(vRayCastFunction);


	if (m_readerFormat.readerType == VV_MULTI_BMP_READER)
	{
		
		reader = vtkSmartPointer<vtkBMPReader>::New();
		vtkBMPReader *bmpReader = vtkBMPReader::SafeDownCast(reader);

		bmpReader->SetFilePrefix(m_readerFormat.filePrefix);
		bmpReader->SetAllow8BitBMP(m_readerFormat.is8Bit);
		bmpReader->SetFileNameSliceOffset(m_readerFormat.imgRngStart);
		bmpReader->SetDataScalarTypeToUnsignedChar();
		bmpReader->SetDataByteOrderToBigEndian();

		bmpReader->SetDataExtent(0, m_readerFormat.dimX,
								 0, m_readerFormat.dimY,
								m_readerFormat.imgRngStart, m_readerFormat.imgRngEnd);

		volumeMapper->SetInputConnection(bmpReader->GetOutputPort());
	}
	/*else if (m_readerFormat.readerType == VV_RAW_IMG_READER)
	{
		reader = vtkSmartPointer<vtkImageReader2>::New();
		rawReader->SetFileName(m_readerFormat.fileName);
		
		if (m_readerFormat.fileByteOrder == VV_BIG_ENDIAN)
			rawReader->SetDataByteOrderToBigEndian();
		else
			rawReader->SetDataByteOrderToLittleEndian();

		rawReader->SetDataExtent(0, m_readerFormat.dimX,
								 0, m_readerFormat.dimY,
								 m_readerFormat.imgRngStart, m_readerFormat.imgRngEnd);
		
		rawReader->SetDataOrigin(0.0, 0.0, 0.0);
		rawReader->SetDataSpacing(m_readerFormat.nSpacingX, 
								  m_readerFormat.nSpacingY, 
								  m_readerFormat.nSpacingZ);

		rawReader->SetDataScalarTypeToUnsignedChar();
		rawReader->UpdateWholeExtent();

		volumeMapper->SetInputConnection(rawReader->GetOutputPort());
	}
	else if (m_readerFormat.readerType == STRUCTURED_POINTS_READER)
	{
		vtkSmartPointer<vtkStructuredPointsReader> vSPReader = vtkSmartPointer<vtkStructuredPointsReader>::New();
		vSPReader->SetFileName(m_readerFormat.fileName);

		volumeMapper->SetInputConnection(vSPReader->GetOutputPort());
	}*/


	volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetColor(volumeColorTransfer);
	volumeProperty->SetScalarOpacity(volumeScalarTransfer);
	volumeProperty->SetGradientOpacity(volumeGradTransfer);
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(m_dAmbient);
	volumeProperty->SetDiffuse(m_dDiffuse);
	volumeProperty->SetSpecular(m_dSpecular);

	//volume given to renderer
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	m_ren->AddViewProp(volume);

	return 1;
}


void VolumeViewer::InitializeRenderer()
{
	//m_camera = m_ren->GetActiveCamera();
	double *c = volume->GetCenter();

	fprintf(stdout, "Focal Pt: (%f, %f, %f)\n", c[0], c[1], c[2]);
	m_camera->SetFocalPoint(c[0], c[1], c[2]);
	m_camera->SetPosition(c[0] + 900, c[1], c[2]);
	m_camera->SetViewUp(0, 0, 1);

	m_ren->SetBackground(1.,1.,1.);
	m_renWin->SetSize(ScreenWidth(), ScreenHeight());

	m_iren->Initialize();
}

bool VolumeViewer::SetColorTransFunc(double scalar, double r, double g, double b)
{
	if (volumeColorTransfer == NULL) volumeColorTransfer = vtkSmartPointer<vtkColorTransferFunction>::New();
	
	volumeColorTransfer->AddRGBPoint(scalar,r,g,b);
	return true;
}

bool VolumeViewer::ClearColorTransFunc(double scalar)
{
	if (volumeColorTransfer == NULL) return false;

	if (scalar == -1.0){ volumeColorTransfer->RemoveAllPoints(); }
	else { volumeColorTransfer->RemovePoint(scalar); }
	return true;
}

bool VolumeViewer::SetScalarTransFunc(double scalar, double opacity)
{
	if (volumeScalarTransfer == NULL) volumeScalarTransfer = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeScalarTransfer->AddPoint(scalar, opacity);
	return true;
}

bool VolumeViewer::ClearScalarTransFunc(double scalar)
{
	if (volumeScalarTransfer == NULL) return false;

	if (scalar == -1.0) { volumeScalarTransfer->RemoveAllPoints(); }
	else {volumeScalarTransfer->RemovePoint(scalar);}
	return true;
}

bool VolumeViewer::SetGradientTransFunc(double gradMag, double opacity)
{
	if (volumeGradTransfer == NULL) volumeGradTransfer = vtkSmartPointer<vtkPiecewiseFunction>::New();

	volumeGradTransfer->AddPoint(gradMag, opacity);
	return true;
}

bool VolumeViewer::ClearGradientTransFunc(double scalar)
{
	if (volumeGradTransfer == NULL) return false;

	if (scalar == -1) { volumeGradTransfer->RemoveAllPoints(); }
	else {volumeGradTransfer->RemovePoint(scalar);}
	return true;
}



/************************************************************************/
/*          Get/Set  Methods                                            */
/************************************************************************/

//int VolumeViewer::ScreenWidth() const
//{
//	return m_screenWidth;
//}
//
//void VolumeViewer::ScreenWidth( int val )
//{
//	m_screenWidth = val;
//}

//int VolumeViewer::ScreenHeight() const
//{
//	return m_screenHeight;
//}
//
//void VolumeViewer::ScreenHeight( int val )
//{
//	m_screenHeight = val;
//}

double VolumeViewer::Ambient() const
{
	return m_dAmbient;
}

void VolumeViewer::Ambient( double val )
{
	m_dAmbient = val;
	volumeProperty->SetAmbient(m_dAmbient);

}

double VolumeViewer::Diffuse() const
{
	return m_dDiffuse;
}

void VolumeViewer::Diffuse( double val )
{
	m_dDiffuse = val;
	volumeProperty->SetDiffuse(m_dDiffuse);

}

double VolumeViewer::Specular() const
{
	return m_dSpecular;
}

void VolumeViewer::Specular( double val )
{
	m_dSpecular = val;
	volumeProperty->SetSpecular(m_dSpecular);
}



vtkSmartPointer<vtkVolumeProperty> VolumeViewer::VolumeProperty() const
{
	return volumeProperty;
}

void VolumeViewer::VolumeProperty( vtkSmartPointer<vtkVolumeProperty> val )
{
	volumeProperty = val;
}



