/********************************************************************
	created:	18:10:2011   11:17
	filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer\Viewer.h
	file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer
	file base:	Viewer
	file ext:	h
	author:		Jim Pelton
	
	purpose:	Abstract viewer class for holding rendering data for vtk.
*********************************************************************/
#ifndef VIEWER_H_
#define VIEWER_H_

#include "DataReaderFormat.h"

#include <vtkSmartPointer.h>
#include <vtkOutputWindow.h>
#include <vtkFileOutputWindow.h>

#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

const float  DEFAULT_AMBIENT  = 0.1;
const float  DEFAULT_DIFFUSE  = 0.4;
const float  DEFAULT_SPECULAR = 0.3;



class Viewer
{
private:
	int m_screenWidth;
	int m_screenHeight;

protected:

	vtkSmartPointer<vtkCamera> m_camera;
	vtkSmartPointer<vtkRenderer> m_ren;
	vtkSmartPointer<vtkRenderWindow> m_renWin;
	vtkSmartPointer<vtkRenderWindowInteractor> m_iren;

    vtkSmartPointer<vtkOutputWindow> outwin;
    vtkSmartPointer<vtkFileOutputWindow> outFileWindow;

	DataReaderFormat m_readerFormat;

	double m_dAmbient;
	double m_dDiffuse;
	double m_dSpecular;


	int setup();

public:
	Viewer(void);
	Viewer(DataReaderFormat & drf, int screenwidth, int screenheight);
	virtual ~Viewer(void);

	//update the pipeline and re-render.
	void Refresh();

	virtual void Start();
	
	//	Initialize the renderer.
	virtual void InitializeRenderer() = 0;


	/************************************************************************/
	/*   Getters/Setters                                                    */
	/************************************************************************/

	 int ScreenWidth() const;
	 void ScreenWidth(int val);
	
	 int ScreenHeight() const;
	 void ScreenHeight(int val);
	
	 double Ambient() const;
	 void Ambient(double val);
	
	 double Specular() const;
	 void Specular(double val);
	
	 double Diffuse() const;
	 void Diffuse(double val);

	vtkSmartPointer<vtkRenderWindow> RenWin() const;
	void RenWin(vtkSmartPointer<vtkRenderWindow> val);
        
	
};
#endif

