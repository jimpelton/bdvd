/********************************************************************
 created:	2:11:2011   12:52
 filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer\SurfaceUtil.cpp
 file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer
 file base:	SurfaceUtil
 file ext:	cpp
 author:		jim

 purpose:	utilities for analyzing a surface.


*********************************************************************/


#include "SurfaceUtil.h"

SurfaceUtil::SurfaceUtil()
{
}

double SurfaceUtil::SurfaceArea(vtkPolyData *pd)
{
	double totArea = 0;
	vtkIdType numCells = pd->GetNumberOfCells();

	vtkTriangle *t;
	double p0[3], p1[3], p2[3];
	for (int i = 0; i < numCells; i++)
	{
		vtkCell *c = pd->GetCell(i);
		if (c->GetCellType() == VTK_TRIANGLE){
			t = vtkTriangle::SafeDownCast(pd->GetCell(i));
			totArea += t->ComputeArea();
		}
		else
		{
			totArea = -1;
			break;
		}
	}
}





