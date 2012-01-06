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
#include "FileWriter.h"

#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>

#include <sstream>

SurfaceUtil::SurfaceUtil()
{
}

/**
 * Compute the average edge length of all of the triangles in the surface.
 * If bins is given then every avg. length is binned with the length as the
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


/**
 * Does what the name suggests.
 * @param volData the image data to extract from.
 * @param ival the iso value to extract.
 * @return the vtkPolyData wrapped in a vtkSmartPointer.
 */
vtkSmartPointer<vtkPolyData> SurfaceUtil::ExtractSingleIsoSurface(vtkAlgorithmOutput *volData, int ival, int normals)
{
	vtkMarchingCubes *mCubesExtractor = vtkMarchingCubes::New();
	mCubesExtractor->SetInputConnection(volData);
	mCubesExtractor->SetValue(0, ival);
	mCubesExtractor->SetComputeNormals(normals);
	mCubesExtractor->Update();
	vtkSmartPointer<vtkPolyData> rval = mCubesExtractor->GetOutput();
	mCubesExtractor->Delete();
	return rval;
}

/**
 * Extract a bunch of iso surfaces with marching cubes, and save them to disk with the specified filename fname.
 * fname is prepended with "isoXX" to distinguish the different surface data from each other.
 * @param volData the image data extract from.
 * @param ivals the array of iso values to extract.
 * @param ivalsLength the number iso values in the array.
 * @param fname  the file name to save to.
 * @return the number of iso values extracted.
 */
int SurfaceUtil::BatchExtractAndSaveIsoSurface(vtkAlgorithmOutput *volData,
		int *ivals, int ivalsLength,
		char *basefname, char *path=".")
{
	vtkSmartPointer<vtkMarchingCubes> mCubesExtractor =
			vtkSmartPointer<vtkMarchingCubes>::New();
	mCubesExtractor->SetInputConnection(volData);
	FileWriter f;
	int curIsoVal = 0;
	for (int i = 0; i < ivalsLength; i++)
	{
		curIsoVal = ivals[i];
		fprintf(stdout, "Processing iso value: %d", curIsoVal);

		mCubesExtractor->SetValue(0, curIsoVal);
		mCubesExtractor->Update();

		std::stringstream ss;
		ss << path << "/";
		ss << "iso" << setfill('0') << setw(4) << ivals[i];
		ss <<  "_" << basefname << "_poly.vtk";


		f.SaveIsoSurfacePolyData(mCubesExtractor->GetOutput(), ss.str().c_str());
		fprintf(stdout, "\nExtracted and saved %s\n", ss.str().c_str());
	}

}


