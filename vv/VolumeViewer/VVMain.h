/********************************************************************
	created:	2011/10/20
	created:	20:10:2011   11:09
	filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer\VVSetup.h
	file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer
	file base:	VVSetup
	file ext:	h
	author:		jim
	
	purpose:	Setup the GUI and place the VTK widget in the QT window.
	            Setup the Viewer object.
*********************************************************************/



#ifndef _GUICLASS_H
#define _GUICLASS_H

#include "VVGui.h"
#include "DataReaderFormat.h"
#include "IsoSurfaceViewer.h"
#include "FileWriter.h"

#include <QtGui/QMainWindow>
#include <QtCore/QObject>




class VVMain : public QMainWindow, public Ui::GUI
{
	

private:
	Q_OBJECT

	IsoSurfaceViewer *viewer;
	DataReaderFormat drf;
	int isoValue;
    double surfaceColor[3];


    void init(DataReaderFormat drf);

	//calculate initial iso value based off histogram
	//currently returns a constant value of 85.
	int calcInitialIsoValue();
    
    void printSetup();

public:
	VVMain(void);
    VVMain(DataReaderFormat drf);
	~VVMain(void);
        
        void InitializeRenderer();

public slots:

	/**
	 * Sets the IsoValue of the vtkMarchingCubes in IsoSurfaceViewer
	 */
	void SetIsoValue(int v);

    void SavePolyDataForIsoSurface();

    void ReadPolyDataForIsoSurface();

	/*
	 *	Set the red, green or blue color value as an integer from 0-255.
	 *  Does not update the render window.
	 */
	void SetRedColorValue(int);
	void SetGreenColorValue(int);
	void SetBlueValue(int);
    
	//update the render window and vtk pipeline.
	void RedrawRenderWindow();

};

#endif







