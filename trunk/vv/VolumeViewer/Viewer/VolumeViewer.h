
#ifndef VOLUMEVIEWER_H
#define VOLUMEVIEWER_H

#include "Viewer.h"
#include "KeypressInteractorStyle.h"

#include <vtkSmartPointer.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>


#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>

#include <vtkImageAlgorithm.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastFunction.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>

#include <vtkPiecewiseFunction.h>
#include <vtkCamera.h>

#include <vector>
#include <string>

class KeypressInteractorStyle;
using std::vector;
using std::string;


class VolumeViewer : public Viewer{

private:

	//TODO: does this actually get deleted in vtkRenderWindowInteractor.cxx, line 117/119?
	KeypressInteractorStyle *m_keypressStyle;
	vtkSmartPointer<vtkCallbackCommand> m_vKeyPressCallback;
	
	vtkSmartPointer<vtkImageAlgorithm> reader;
	
	vtkSmartPointer<vtkVolumeRayCastFunction> vRayCastFunction;
	vtkSmartPointer<vtkVolume> volume;
	vtkSmartPointer<vtkVolumeMapper> volumeMapper;
	vtkSmartPointer<vtkVolumeProperty> volumeProperty; 
	
	
	vtkSmartPointer<vtkColorTransferFunction> volumeColorTransfer;
	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarTransfer;
	vtkSmartPointer<vtkPiecewiseFunction> volumeGradTransfer;
	
private:
	/* do misc. assignments at init time*/
	void assignDefaults();

public:

	VolumeViewer(void);
	VolumeViewer(DataReaderFormat & drf, int screenwidth, int screenheight);
	virtual ~VolumeViewer(void);

	
	int Setup();

	/**
	 *	Add a vtkColorTransferFunction with these parameters
	 *	to the volume property.
	 *  
	 *	Set the vtkColorTransferFunction in volumeColorTransfer directly
	 *	without adding it to the volumeColorTransferFuncs vector.
	 */
	//bool AddColorTransFunc(double scalar, double r, double g, double b);
	bool SetColorTransFunc(double scalar, double r, double g, double b);
	bool ClearColorTransFunc(double scalar);
	
	/**
	 *	Add a these related parameters to the vtkPiecewiseFunction
	 *	used for the ScalarOpacity values for the volume mapper.
	 *	
	 *	Set the vtkScalarTransferFunction in volumeScalarFunction...
	 */
	//bool AddScalarTransFunc(double scalar, double opacity);
	bool SetScalarTransFunc(double scalar, double opacity);
	bool ClearScalarTransFunc(double scalar);
	
	/**
	 *	Add these related parameters to the vtkPiecewiseFunction
	 *	used for the GradientOpacity values for the volume mapper.
	 */
	//bool AddGradientTransFunc(double gradMag, double opacity);
	bool SetGradientTransFunc(double gradMag, double opacity);
	bool ClearGradientTransFunc(double scalar);
	

	/**
	 *	Initialize the vtk renderer. Does not start the actual loop.
	 *  The render loop should be started by qtvtkwidget.

		overridden from viewer
	 */
	void InitializeRenderer();



	 //int ScreenWidth() const;
	 //void ScreenWidth(int val);

	 //int ScreenHeight() const;
	 //void ScreenHeight(int val);

	 double Ambient() const;
	 void Ambient(double val);

	 double Specular() const;
	 void Specular(double val);

	 double Diffuse() const;
	 void Diffuse(double val);


	vtkSmartPointer<vtkVolumeProperty> VolumeProperty() const;
	void VolumeProperty(vtkSmartPointer<vtkVolumeProperty> val);
	
};

#endif
