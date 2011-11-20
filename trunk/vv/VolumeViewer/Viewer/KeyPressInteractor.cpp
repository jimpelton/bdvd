#include "KeypressInteractorStyle.h"
#include <iostream>
#include <sstream>
//#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

KeypressInteractorStyle::KeypressInteractorStyle(void)
{
	uim = new UIMain;
}
KeypressInteractorStyle::~KeypressInteractorStyle(void)
{
	delete uim;
}


void KeypressInteractorStyle::OnKeyPress()
{
	vtkRenderWindowInteractor *iren = this->Interactor;
	vtkRenderer *ren = this->GetCurrentRenderer();
	vtkRenderWindow *renWin = ren->GetRenderWindow();


	char keyCode = iren->GetKeyCode();
	//fprintf(stdout, "Pressed: %s is %d\n", iren->GetKeySym(), keyCode);
	switch (keyCode)
	{
	case 'b':
		bgSwitch(renWin, ren);
		break;
	case 'c':
		uim->Start();
		break;
	}


	vtkInteractorStyleTrackballCamera::OnKeyPress();
}

void KeypressInteractorStyle::handlePlus()
{
	fprintf(stdout, "Inside handlePlus()\n");
}

void KeypressInteractorStyle::handleMinus()
{
	fprintf(stdout, "Inside handleMinus()\n");
}

void KeypressInteractorStyle::bgSwitch(vtkRenderWindow *rw, vtkRenderer *ren)
{
	//fprintf(stdout, "Setting background...\n");

	double * bkgnd = ren->GetBackground();
	if (bkgnd[0] == 0){
		ren->SetBackground(1,1,1);
	}else{
		ren->SetBackground(0,0,0);
	}

	rw->Render();
}

void KeypressInteractorStyle::SetVolumeViewer(VolumeViewer *viewer)
{
	myViewer = viewer;
	uim->SetVolumeViewer(myViewer);
}
