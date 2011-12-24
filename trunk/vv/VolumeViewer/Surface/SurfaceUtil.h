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


class SurfaceUtil
{
public:


public:
    SurfaceUtil();

    //static void CountTris(vtkPolyData *);
    //static void CountVerts(vtkPolyData *);
    //static void CellArray(vtkPolyData *);
    static double SurfaceArea(vtkPolyData *);
    static double TriangleAvgEdgeLength(vtkPolyData*);



};

#endif // SURFACEUTIL_H
