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

//#include <vtkCamera.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkInteractorStyleTrackballCamera.h>


class Viewer
{
private:
	int m_screenWidth;
	int m_screenHeight;

protected:
    vtkSmartPointer<vtkOutputWindow> outwin;
    vtkSmartPointer<vtkFileOutputWindow> outFileWindow;
	DataReaderFormat m_readerFormat;

	Viewer(void);
	Viewer(DataReaderFormat & drf, int screenwidth, int screenheight);
	virtual ~Viewer(void);

public:

	//update the pipeline and re-render.
	virtual void Refresh() = 0;

	//	Initialize the renderer.
	virtual void InitializeRenderer() = 0;

	//initialize this object at the users lesure.
	//returns 1 if success, returns 0 if failure.
	virtual int Setup() = 0;

	virtual void Start();


	/************************************************************************/
	/*   Getters/Setters                                                    */
	/************************************************************************/

	 int ScreenWidth() const;
	 void ScreenWidth(int val);
	
	 int ScreenHeight() const;
	 void ScreenHeight(int val);
};
#endif

