/********************************************************************
 created:	2011/10/18
 created:	18:10:2011   11:20
 filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer\Viewer.cpp
 file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer
 file base:	Viewer
 file ext:	cpp
 author:		jim

 purpose:	Abstract viewer class for holding rendering data for vtk.
*********************************************************************/


#include "Viewer.h"


Viewer::Viewer(void)
{}

Viewer::Viewer(DataReaderFormat &drf, int screenwidth, int screenheight)
{
    m_readerFormat = drf;
    m_screenWidth = screenwidth;
    m_screenHeight= screenheight;

    outFileWindow = vtkSmartPointer<vtkFileOutputWindow>::New();
    outFileWindow->SetFileName( "viewer_log.txt" );
    outwin = vtkOutputWindow::GetInstance();

    if (outwin) outwin->SetInstance(outFileWindow);

    //viewer_setup();
}

Viewer::~Viewer(void){}



/************************************************************************/
/* Getters/Setters                                                      */
/************************************************************************/

int Viewer::ScreenWidth() const
{
    return m_screenWidth;
}

void Viewer::ScreenWidth( int val )
{
    m_screenWidth = val;
}

int Viewer::ScreenHeight() const
{
    return m_screenHeight;
}

void Viewer::ScreenHeight( int val )
{
    m_screenHeight = val;
}

/*
*  Start the render loop.
*  This method is for added support for a stand alone vtk window. 
*  If this Viewer is embedded in a qt window, then the QtVTKWidget
*  should take care of starting the render loop.
*  Unless it is overridden, this function does nothing.
*/
void Viewer::Start(){}
