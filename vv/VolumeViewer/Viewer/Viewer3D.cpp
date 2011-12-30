/*
 * Viewer3D.cpp
 *
 *  Created on: Dec 29, 2011
 *      Author: jim
 */

#include "Viewer3D.h"

Viewer3D::Viewer3D(): Viewer() {}

Viewer3D::Viewer3D(DataReaderFormat &drf, int screenwidth, int screenheight)
	: Viewer(drf, screenwidth, screenheight)
{
	viewer_setup();
}

Viewer3D::~Viewer3D() {}

int Viewer3D::viewer_setup(){

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

void Viewer3D::Refresh()
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

vtkSmartPointer<vtkRenderWindow> Viewer3D::RenWin() const
{
    return m_renWin;
}

void Viewer3D::RenWin( vtkSmartPointer<vtkRenderWindow> val )
{
    m_renWin = val;
}

double Viewer3D::Ambient() const
{
    return m_dAmbient;
}

void Viewer3D::Ambient( double val )
{
    m_dAmbient = val;

}

double Viewer3D::Diffuse() const
{
    return m_dDiffuse;
}

void Viewer3D::Diffuse( double val )
{
    m_dDiffuse = val;

}

double Viewer3D::Specular() const
{
    return m_dSpecular;
}

void Viewer3D::Specular( double val )
{
    m_dSpecular = val;
}
