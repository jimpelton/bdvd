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

	virtual int viewer_setup() = 0;

	Viewer(void);
	Viewer(DataReaderFormat & drf, int screenwidth, int screenheight);
	virtual ~Viewer(void);

public:
	//update the pipeline and re-render.
	virtual void Refresh() = 0;

	virtual void Start();
	
	//	Initialize the renderer.
	virtual void InitializeRenderer() = 0;
	/*
	 *  Setup the vtk pipeline, the marching cubes extractor, etc.
	 *  Chooses the correct reader from the DataReaderFormat.
	 *  @return 0 on failure, 1 on success.
	 */
	virtual int Setup() = 0;

	/************************************************************************/
	/*   Getters/Setters                                                    */
	/************************************************************************/

	 int ScreenWidth() const;
	 void ScreenWidth(int val);
	
	 int ScreenHeight() const;
	 void ScreenHeight(int val);
};
#endif

