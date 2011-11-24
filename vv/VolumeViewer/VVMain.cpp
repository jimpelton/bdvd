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
#include <strstream>
#include <ctime>

int ISO_SURFACE = 1;

int DEFAULT_SCREEN_WIDTH  = 640;
int DEFAULT_SCREEN_HEIGHT = 480;

int DEFAULT_WINDOW_WIDTH = 1280;
int DEFAULT_WINDOW_HEIGHT = 720;

int DEFAULT_INITIAL_COLOR_RED   = 228;
int DEFAULT_INITIAL_COLOR_GREEN = 225;
int DEFAULT_INITIAL_COLOR_BLUE  = 216;
int DEFAULT_INITIAL_COLOR_ALPHA = 200;

int DEFAULT_INITIAL_ISO_SLIDER_MAX = 150;
int DEFAULT_INITIAL_ISO_SLIDER_MIN = 1;
int CURRENT_ISO_VALUE = 55;

char *DEFAULT_SAVE_POLYDATA_FNAME = "pdata.vtk";
int DEFAULT_SAVE_POLYDATA_FNAME_LENGTH = 9;

VVMain::VVMain(DataReaderFormat readerFormat)
{
    drf = readerFormat;
    init(drf);
}

VVMain::VVMain(void)
{}


VVMain::~VVMain(void)
{
}

void VVMain::init(DataReaderFormat drf)
{

    surfaceColor[0] = surfaceColor[1] = surfaceColor[2] = 1.0;

    
    //figure out what kind of files we're using.
   
    this->SetupUi(this, drf);

    if (ISO_SURFACE){
        printSetup();

        viewer = new IsoSurfaceViewer(drf, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
            CURRENT_ISO_VALUE, IsoSurfaceViewer::CON_FILTER );

        if (!viewer->Setup()){
            fprintf(stdout, "Setup failed!\n");
        }

        viewer->InitializeRenderer();        
        GetVtkWidget()->SetRenderWindow(viewer->RenWin());

    }
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
    fprintf(stdout, "\n\tISO VALUE: %d\n", CURRENT_ISO_VALUE);
}

/*
 *	Currently only returns integral value.
 */
int VVMain::calcInitialIsoValue()
{
	return CURRENT_ISO_VALUE;
}


/************************************************************************/
/* SIGNALS AND SLOTS HANDLERS.                                          */
/************************************************************************/

/*
 *	Set the Iso Value for the associated viewer.
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
void VVMain::SavePolyDataForIsoSurface()
{
    FileWriter f;
    const int timeNameLength = 21;
    char timeName[timeNameLength];  //MMDD_HHMM_pdata.vpd
    
    time_t theTime = time(0);
    tm * now = localtime(&theTime);
    strftime(timeName, timeNameLength*sizeof(char), "%m%d_%H%M%S_", now);  //MMDD_HHMM_
    
   std::string name;
   name.append(timeName);
   name.append(DEFAULT_SAVE_POLYDATA_FNAME);

   int ecode = f.SaveIsoSurfacePolyData(viewer->GetPolyData(), name.c_str());
    
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
 */
void VVMain::RedrawRenderWindow()
{
    viewer->SetColorRGB(surfaceColor);
    viewer->IsoValue(isoValue);
    viewer->Refresh();
}
