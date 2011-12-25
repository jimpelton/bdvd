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

Viewer::Viewer(DataReaderFormat & drf, int screenwidth, int screenheight)
{
    m_readerFormat = drf;
    m_screenWidth = screenwidth;
    m_screenHeight= screenheight;

    outFileWindow = vtkSmartPointer<vtkFileOutputWindow>::New();
    outFileWindow->SetFileName( "viewer_log.txt" );
    outwin = vtkOutputWindow::GetInstance();

    if (outwin) outwin->SetInstance(outFileWindow);
    

    setup();
}

Viewer::~Viewer(void){}

/**
 *   protected method called from Viewer's constructor.
 *   Inits the renderer, render window, interactor, camera.
 *  
 *  @return always returns 1
 */
int Viewer::setup(){

    //rendering setup
    m_ren = vtkSmartPointer<vtkRenderer>::New();

    m_renWin = vtkSmartPointer<vtkRenderWindow>::New();
    m_renWin->AddRenderer(m_ren);

    m_iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    m_camera = vtkSmartPointer<vtkCamera>::New();
    m_ren->SetActiveCamera(m_camera);


    m_dAmbient  = DEFAULT_AMBIENT;
    m_dDiffuse  = DEFAULT_DIFFUSE;
    m_dSpecular = DEFAULT_SPECULAR;

    return 1;
}

/*
 *  Calls RenWin()->Render(), which updates the vtk pipeline and re-renders the
 *  scene.
 */
void Viewer::Refresh()
{
    RenWin()->Render();
    RenWin()->CheckGraphicError();
    const char *er = RenWin()->GetLastGraphicErrorString();
    if (er){
        fprintf(stdout, "Viewer::Refresh RESULT: %s\n", er);
    }
}



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

double Viewer::Ambient() const
{
    return m_dAmbient;
}

void Viewer::Ambient( double val )
{
    m_dAmbient = val;

}

double Viewer::Diffuse() const
{
    return m_dDiffuse;
}

void Viewer::Diffuse( double val )
{
    m_dDiffuse = val;

}

double Viewer::Specular() const
{
    return m_dSpecular;
}

void Viewer::Specular( double val )
{
    m_dSpecular = val;
}


vtkSmartPointer<vtkRenderWindow> Viewer::RenWin() const
{
    return m_renWin;
}

void Viewer::RenWin( vtkSmartPointer<vtkRenderWindow> val )
{
    m_renWin = val;
}


/*
*  Start the render loop.
*  This method is for added support for a stand alone vtk window. 
*  If this Viewer is embedded in a qt window, then the QtVTKWidget
*  should take care of starting the render loop.
*  Unless it is overridden, this function does nothing.
*/
void Viewer::Start(){}
