/*
 * Viewer3D.h
 *
 *  Created on: Dec 29, 2011
 *      Author: jim
 */

#ifndef VIEWER3D_H_
#define VIEWER3D_H_

#include "DataReaderFormat.h"
#include "Viewer.h"


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

class Viewer3D: public Viewer {

protected:
	vtkSmartPointer<vtkCamera> m_camera;
	vtkSmartPointer<vtkRenderer> m_ren;
	vtkSmartPointer<vtkRenderWindow> m_renWin;
	vtkSmartPointer<vtkRenderWindowInteractor> m_iren;

	double m_dAmbient;
	double m_dDiffuse;
	double m_dSpecular;

	int viewer_setup();

public:
	Viewer3D();
	Viewer3D(DataReaderFormat &drf, int, int);
	virtual ~Viewer3D();

	virtual void Refresh();
	//virtual void InitializeRenderer() = 0;
	//virtual int Setup() = 0;

	/************************************************************************/
	/*   Getters/Setters                                                    */
	/************************************************************************/

public:

	 double Ambient() const;
	 void Ambient(double val);

	 double Specular() const;
	 void Specular(double val);

	 double Diffuse() const;
	 void Diffuse(double val);

	vtkSmartPointer<vtkRenderWindow> RenWin() const;
	void RenWin(vtkSmartPointer<vtkRenderWindow> val);
};

#endif /* VIEWER3D_H_ */
