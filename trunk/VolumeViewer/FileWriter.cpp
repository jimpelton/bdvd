#include "FileWriter.h"

FileWriter::FileWriter()
{
}


/**
 * Given a vtkPolyData and file name, writes that data to a vtk file with that file name.
 *
 * Returns 1 on success, 0 if there was an oops.
 */
int FileWriter::SaveIsoSurface(vtkPolyData *vpd, char * fname)
{
	vtkPolyDataWriter *writer = vtkPolyDataWriter::New();
	writer->SetInput(vpd);
	writer->SetFileName(fname);
	writer->Update();

	return 1;
}
