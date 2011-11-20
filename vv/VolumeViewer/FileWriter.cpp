#include "FileWriter.h"

FileWriter::FileWriter()
{
}


/**
 * Given a vtkPolyData and file name, writes that data to a vtk file with that file name.
 *
 * Returns the error code from the file writer.
 */
int FileWriter::SaveIsoSurfacePolyData(vtkPolyData *vpd, const char * fname)
{
	vtkPolyDataWriter *writer = vtkPolyDataWriter::New();
	writer->SetInput(vpd);
	writer->SetFileName(fname);
    writer->SetFileTypeToBinary();
	writer->Update();
    return writer->GetErrorCode();	
}
