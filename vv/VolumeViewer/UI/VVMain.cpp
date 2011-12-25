/********************************************************************
	created:	2:11:2011   12:52
	filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer\VVMain.cpp
	file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer
	file base:	VVMain
	file ext:	cpp
	author:		jim
	
	purpose:	Setup the viewer with filename, other intial components.
	            Pass messages from the VVGui to the viewer component.
				
				NOTE: This file requires that it be MOC'd after any changes and 
				prior to compilation with cl.exe or gcc (win and linux).
*********************************************************************/



#include "Common.h"
#include "VVMain.h"
#include "VolumeViewer.h"
#include "IsoSurfaceViewer.h"

#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkPNGReader.h"
#include "vtkTestUtilities.h"

#include <string>
#include <sstream>
#include <ctime>
#include <map>

//int ISO_SURFACE = 1;

int DEFAULT_SCREEN_WIDTH  = 640;   //rener window width
int DEFAULT_SCREEN_HEIGHT = 480;   //rener window height.

int DEFAULT_WINDOW_WIDTH = 1280;   
int DEFAULT_WINDOW_HEIGHT = 720;

int DEFAULT_INITIAL_COLOR_RED   = 228;
int DEFAULT_INITIAL_COLOR_GREEN = 225;
int DEFAULT_INITIAL_COLOR_BLUE  = 216;
int DEFAULT_INITIAL_COLOR_ALPHA = 255;

int DEFAULT_INITIAL_ISO_SLIDER_MAX = 255;
int DEFAULT_INITIAL_ISO_SLIDER_MIN = 1;
int DEFAULT_ISO_VALUE = 55;

/*
 *  The default name to append to the polydata file name
 *  after the time and date.
 */
char *DEFAULT_SAVE_POLYDATA_FNAME = "pdata.vtk";
int DEFAULT_SAVE_POLYDATA_FNAME_LENGTH = 9;

char *DEFAULT_SAVE_SCREENSHOT_FNAME = "capture.png";

VVMain::VVMain(DataReaderFormat readerFormat)
{
	viewer=NULL;
	ViewerOptions tmpVO = {1, 0.0, 0.0, 0.0};
    init(readerFormat, tmpVO);
}

VVMain::VVMain(DataReaderFormat drf, ViewerOptions vo)
{
	viewer = NULL;
	init(drf, vo);
}

VVMain::VVMain(void)
{
	viewer=NULL;
}


VVMain::~VVMain(void)
{
	//delete viewer;
}

void VVMain::init(DataReaderFormat drf, ViewerOptions opts)
{
	this->drf = drf;
	this->m_vo = opts;


    surfaceColor[0] = surfaceColor[1] = surfaceColor[2] = 1.0;
    isoValue = DEFAULT_ISO_VALUE;
   
    this->SetupUi(this, drf);

   // if (m_vo.extractISOSurface){
        viewer = new IsoSurfaceViewer(drf, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
            isoValue, IsoSurfaceViewer::CON_FILTER );

        printSetup();

        double r[] = {m_vo.rotX, m_vo.rotY, m_vo.rotZ};
        viewer->SetRotate(r);

        if (viewer->Setup()){
            fprintf(stdout, "Setup failed!\n");
            return;
        }

        printSurfaceStats();

  //  }
}

void VVMain::InitializeRenderer()
{
     viewer->InitializeRenderer();   
     GetVtkWidget()->SetRenderWindow(viewer->RenWin());
}

void VVMain::printSetup()
{
    fprintf(stdout, "\nUsing these *initial* settings: \n" \
        "\tFileName: %s\n" \
        "\tFilePrefix: %s\n" \
        "\tDimensions: %d, %d\n" \
        "\tImage Range: %d-%d\n" \
        "\tIs8bit: %s\n" \
        "\tByte order: %s\n",
        drf.fileName,
        drf.filePrefix, 
        drf.dimX, drf.dimY, 
        drf.imgRngStart, drf.imgRngEnd,
        drf.is8Bit == 0 ? "No" : "Yes", 
        drf.fileByteOrder == VV_BIG_ENDIAN ? "BIG ENDIAN" : "LITTLE ENDIAN");
    fprintf(stdout, "\n\tISO VALUE: %d\n", viewer->IsoValue());
}

void VVMain::printSurfaceStats()
{
	double area = SurfaceUtil::SurfaceArea(viewer->GetPolyData());
	std::map<double, long> *avglengths = new std::map<double, long>();
	double avglng = SurfaceUtil::TriangleAvgEdgeLength(viewer->GetPolyData(), avglengths);

	fprintf(stdout, "Surface Stats: (iso val: %d)\n \tavg length: %f\n \tsfc area:%f \n", viewer->IsoValue(), avglng, area);
	fprintf(stdout, "Number of unique triangle edge length averages: %d\n", avglengths->size());
	delete avglengths;
}

/*
 *	Currently only returns integral value.
 */
int VVMain::calcInitialIsoValue()
{
	return DEFAULT_ISO_VALUE;
}

/*
 * set timeName to a formatted string that is _MMDD_HMS_
 */
void VVMain::fileNameTimeString_MMDDHMS(char *timeName, int timeNameLength)
{
	time_t theTime = time(0);
	tm * now = localtime(&theTime);
	strftime(timeName, timeNameLength*sizeof(char), "_%m%d_%H%M%S_", now);  //MMDD_HHMMSS_
}

/*
 * save a screen shot with s being a string with a unique identifying feature
 * The unique feature could be the system time, such as MMDD_HMS.
 */
void VVMain::saveScreenShot(const char * s)
{
	const int timeNameLength = 21;
	char timeName[timeNameLength];

	vtkRenderWindow *renwin = viewer->RenWin();
	std::stringstream ss;
	ss << viewer->IsoValue() << s << DEFAULT_SAVE_SCREENSHOT_FNAME;
	std::string fname = ss.str();

	FileWriter f;
	f.SaveScreenShot(viewer->RenWin(), fname.c_str());
}

/************************************************************************/
/* SIGNALS AND SLOTS HANDLERS.                                          */
/************************************************************************/

/*
 *	SLOT.
 *
 *	Called when the isovalue slider is moved.
 */
void VVMain::SetIsoValue(int val)
{
	isoValue = val;
	isoEdit->setText(QString::number(val));
}


/**
 *    SLOt.
 * 
 * Called when saving a polydata file with the gui.
 */
int VVMain::SavePolyDataForIsoSurface()
{
    FileWriter f;
    const int timeNameLength = 21;
    char timeName[timeNameLength];  //MMDD_HHMM_pdata.vpd
    

    fileNameTimeString_MMDDHMS(timeName, timeNameLength);
    
    std::string s;
    std::stringstream ss;
    ss << viewer->IsoValue() << timeName << DEFAULT_SAVE_POLYDATA_FNAME;
    s = ss.str();

   int ecode = f.SaveIsoSurfacePolyData(viewer->GetPolyData(), s.c_str());
   fprintf(stdout, "ecode: %d\n", ecode);

   if (this->saveScreenShotWithSurfaceCheckBox->isChecked())
   {
	   saveScreenShot(timeName);
   }

   return ecode;
}




/*
 * SLOT.
 * 
 * Called when opening a poly data file with the GUI
 */
void VVMain::ReadPolyDataForIsoSurface()
{
    
}

/*
 *	SLOT.
 *
 *  Called when slider is changed.
 *  Normalize and set the red color for the surface.
 *  Does not update the render window.
 */
void VVMain::SetRedColorValue( int red )
{
	this->redEdit->setText(QString::number(red));
	surfaceColor[0] = red / 255.f;
}

/*
 *	SLOT.
 *
 *  Called when slider is changed.
 *  Normalize and set the green color for the surface.
 *  Does not update the render window.
 */
void VVMain::SetGreenColorValue( int green )
{
	this->greenEdit->setText(QString::number(green));
	surfaceColor[1] = green / 255.f;
}

/*
 *	SLOT.
 *
 *  Called when slider is changed.
 *	Normalize and set the blue color for the surface.
 *  Does not update the render window.
 */
void VVMain::SetBlueValue( int blue )
{
	this->blueEdit->setText(QString::number(blue));
	surfaceColor[2] = blue / 255.f;
}

/*
 *	SLOT.
 *
 *  call Refresh() on the viewer, which updates the pipeline.
 *  Also saves the current color as was specified by the color sliders/edits.
 *  Also saves the current iso-value as specified by the iso slider/edit.
 */
void VVMain::RedrawRenderWindow()
{
	viewer->SetColorRGB(surfaceColor);
	if (drf.readerType != VV_POLY_DATA_READER){
		bool ok = true;
		isoValue = this->isoEdit->text().toInt(&ok, 10);
		this->isoSlider->setValue(isoValue);
		if (!ok) return;
		viewer->IsoValue(isoValue);
	}
	viewer->Refresh();
	printSurfaceStats();
}
