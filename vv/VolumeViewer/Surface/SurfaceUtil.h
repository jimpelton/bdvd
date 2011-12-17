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


class SurfaceUtil
{
public:


public:
    SurfaceUtil();

    void CountTris(vtkPolyData *);
    void CountVerts(vtkPolyData *);
    void CellArray(vtkPolyData *);
    double SurfaceArea(vtkPolyData *);



};

#endif // SURFACEUTIL_H
