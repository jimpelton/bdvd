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
 * If bins is given then every avg. length is binned into the map with the length as the
 * key and the frequency of the length as the mapped value.
 *
 * @param pd the polydata of the surface.
 * @param bins optional bin for lengths.
 * @return The avg length for all of the triangles in the polydata, or -1.0 if there was a cell that
 *         was not a triangle.
 */
double SurfaceUtil::TriangleAvgEdgeLength(vtkPolyData *pd, std::map<double, long> *bins)
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

			if (bins)
				(*bins)[edgeLen]++;

			avgLength += edgeLen;

		}else{
			avgLength = -1.0;
			break;
		}
	}

	return avgLength / (double)numCells;
}





/**
 * Adds up the triangle surface areas for the given vtkPolyData. If
 * a non-triangle cell is encountered the method returns -1.0;
 * @param pd the polydata to calc the surface area of.
 * @return the surface area as a double, or -1.0 on error.
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





