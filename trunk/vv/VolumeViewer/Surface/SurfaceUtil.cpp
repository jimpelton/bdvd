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

/**
 * Compute the average length of all of the triangles in the surface.
 * @param pd the polydata of the surface.
 * @return The avg length for all of the triangles in the polydata, or -1.0 if there was a cell that
 *         was not a triangle.
 */
double SurfaceUtil::TriangleAvgEdgeLength(vtkPolyData *pd)
{
	double avgLength = 0.0;
	vtkIdType numCells = pd->GetNumberOfCells();


	for (int i = 0; i<numCells; i++)
	{
		vtkCell *c = pd->GetCell(i);
		if (c->GetCellType() == VTK_TRIANGLE)
		{
			vtkTriangle *t = vtkTriangle::SafeDownCast(c);
			vtkLine *e0 = vtkLine::SafeDownCast(t->GetEdge(0));
			vtkLine *e1 = vtkLine::SafeDownCast(t->GetEdge(1));
			vtkLine *e2 = vtkLine::SafeDownCast(t->GetEdge(2));

			double edgeLen = e0->GetLength2();
			edgeLen += e1->GetLength2();
			edgeLen += e2->GetLength2();
			edgeLen /= 3.0;
			avgLength += edgeLen;

		}else{
			avgLength = -1.0;
			break;
		}
	}

	return avgLength / (double)numCells;
}

/**
 *
 * @param pd
 * @return
 */
double SurfaceUtil::SurfaceArea(vtkPolyData *pd)
{
	double totArea = 0.0;
	vtkIdType numCells = pd->GetNumberOfCells();

	vtkTriangle *t;
	for (int i = 0; i < numCells; i++)
	{
		vtkCell *c = pd->GetCell(i);
		if (c->GetCellType() == VTK_TRIANGLE){
			t = vtkTriangle::SafeDownCast(c);
			totArea += t->ComputeArea();
		}
		else
		{
			totArea = -1.0;
			break;
		}
	}
	return totArea;
}





