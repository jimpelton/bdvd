

#include "FileWriter.h"

FileWriter::FileWriter()
{
}

FileWriter::~FileWriter(){}

/**
 * Given a vtkPolyData and file name, writes that data to a vtk file with that file name.
 * The file is a binary vtk polydata  file.
 *
 * Returns the error code from the file writer.
 */
int FileWriter::SaveIsoSurfacePolyData(vtkPolyData *vpd, const  char * fname)
{
	vtkPolyDataWriter *writer = vtkPolyDataWriter::New();
	writer->SetInput(vpd);
	writer->SetFileName(fname);
    writer->SetFileTypeToBinary();
	writer->Update();
    int ecode = writer->GetErrorCode();
    writer->Delete();
    return 	ecode;
}


/**
 * Given a filename, open and read that file.
 *
 * Returns NULL if the file isn't a valid polydata file.
 * Returns a vtkPolyData if the file is a vtk polydata file.
 */
vtkPolyData *FileWriter::ReadIsoSurfacePolyData(const char *fileName)
{
    vtkPolyDataReader *reader = vtkPolyDataReader::New();
    reader->SetFileName(fileName);
    if (!reader->IsFilePolyData()) return NULL;
    reader->Update();
    vtkPolyData *data = reader->GetOutput();
    reader->Delete();
    return data;
}

void FileWriter::SaveScreenShot(vtkRenderWindow *renwin, const char *fileName)
{
	vtkWindowToImageFilter *windowToImageFilter = vtkWindowToImageFilter::New();
	  windowToImageFilter->SetInput(renwin);
	  windowToImageFilter->SetMagnification(3);
	  windowToImageFilter->SetInputBufferTypeToRGBA();
	  windowToImageFilter->Update();

	  vtkPNGWriter *writer = vtkPNGWriter::New();
	  writer->SetFileName(fileName);
	  writer->SetInput(windowToImageFilter->GetOutput());
	  writer->Write();

	  windowToImageFilter->Delete();
	  writer->Delete();

}
