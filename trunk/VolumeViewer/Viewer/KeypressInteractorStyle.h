

/************************************************************************
 * KeypressInteractorStyle.h
 *
 * 
 * //TODO: make work with vtkSmartPointer
************************************************************************/

#ifndef KEYPRESSINTERACTORSTYLE_H
#define KEYPRESSINTERACTORSTYLE_H

#include "VolumeViewer.h"
#include "../UIMain.h"
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vector>
#include <string>

class VolumeViewer;
class UIMain;




class KeypressInteractorStyle : public vtkInteractorStyleTrackballCamera
{

private:
	VolumeViewer *myViewer;
	UIMain *uim;
	void bgSwitch(vtkRenderWindow *rw, vtkRenderer *ren);
	void handlePlus();
	void handleMinus();

public:

	//static KeypressInteractorStyle* New();
	//vtkTypeMacro(KeypressInteractorStyle, vtkInteractorStyleTrackballCamera);

	KeypressInteractorStyle(void);
	~KeypressInteractorStyle(void);
	virtual void OnKeyPress();

	void SetVolumeViewer(VolumeViewer *);

};

//vtkStandardNewMacro(KeypressInteractorStyle);

#endif