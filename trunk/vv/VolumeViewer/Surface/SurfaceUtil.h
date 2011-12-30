/********************************************************************
 created:	2:11:2011   12:52
 filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer\SurfaceUtil.h
 file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer
 file base:	SurfaceUtil
 file ext:	h
 author:		jim

 purpose:	utilities for analyzing a surface.


*********************************************************************/
#ifndef SURFACEUTIL_H
#define SURFACEUTIL_H

#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkCell.h>
#include <vtkTriangle.h>
#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkAlgorithmOutput.h>
#include <vtkMarchingCubes.h>
#include <vtkSmartPointer.h>

#include <map>

class SurfaceUtil
{
private:



public:
    SurfaceUtil();

    //static void CountTris(vtkPolyData *);
    //static void CountVerts(vtkPolyData *);
    //static void CellArray(vtkPolyData *);
    static double SurfaceArea(vtkPolyData *);
    static double TriangleAvgEdgeLength(vtkPolyData* surface, std::map<double, long> *bins = NULL);
    static vtkSmartPointer<vtkPolyData> ExtractSingleIsoSurface(vtkAlgorithmOutput *volData, int ival, int normals);
    static int BatchExtractAndSaveIsoSurface(vtkAlgorithmOutput *volData, int *ivals, int ivalsLength, char *fname);
};

#endif // SURFACEUTIL_H
