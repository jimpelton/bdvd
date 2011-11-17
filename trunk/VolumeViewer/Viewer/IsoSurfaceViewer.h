/********************************************************************
	created:	19:10:2011   15:38
	filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer\IsoSurfaceViewer.h
	file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer
	file base:	IsoSurfaceViewer
	file ext:	h
	author:		jim
	
	purpose:	Concrete extension of Viewer for rendering iso surfaces with
	            vtkMarchingCubes m_algorithm.
*********************************************************************/
#ifndef ISOSURFACEVIEWER_H_
#define ISOSURFACEVIEWER_H_

#include "Viewer.h"
#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkMarchingCubes.h>

#include <vtkExtractVOI.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODActor.h>
#include <vtkProperty.h>
#include <vtkAlgorithmOutput.h>
//#include <vtkDecimatePro.h>
#include <vtkAppendPolyData.h>
#include <vtkDataSetMapper.h>


class IsoSurfaceViewer : public Viewer
{

private:
    

	int m_iso_value;
	double m_surfaceColor[3];
    int m_algorithm;
   
    vtkAlgorithmOutput *getAlgoOutput();

protected:
	
	vtkSmartPointer<vtkBMPReader> reader;
	vtkSmartPointer<vtkPolyDataAlgorithm> extractor;
    vtkSmartPointer<vtkPolyDataAlgorithm> extractor2;

	
	vtkSmartPointer<vtkPolyDataMapper> polyDataMapper;
    vtkSmartPointer<vtkPolyDataMapper> polyDataMapper2;

    vtkSmartPointer<vtkExtractVOI> voiExtractor;
    vtkSmartPointer<vtkExtractVOI> voiExtractor2;
    
    vtkSmartPointer<vtkAppendPolyData> appendFilter;

    vtkSmartPointer<vtkPolyDataConnectivityFilter> conFilter;
    vtkSmartPointer<vtkPolyDataConnectivityFilter> conFilter2;

    //vtkSmartPointer<vtkPoint
    
    vtkSmartPointer<vtkLODActor> surface;
    vtkSmartPointer<vtkLODActor> surface2;

	
public:
	IsoSurfaceViewer(void);
	IsoSurfaceViewer(DataReaderFormat & drf, int screenwidth, int screenheight,
        int iso_val, int algorithm);
	~IsoSurfaceViewer(void);

   enum Algos{ NONE = 0, CON_FILTER = 1 };

	int Setup();
	void InitializeRenderer();

	vtkPolyData* GetPolyData();

/************************************************************************/
/*     Getters/Setters                                                  */
/************************************************************************/
	int IsoValue() const;
	void IsoValue(int val);

	vtkSmartPointer<vtkLODActor> Surface() const;
	void Surface(vtkSmartPointer<vtkLODActor> val);

	void SetColorRed  (double red);
	void SetColorGreen(double green);
	void SetColorBlue (double blue);
    void SetColorRGB(double * rgb);

    int Algorithm() const;
    void Algorithm(int val);

};



#endif
