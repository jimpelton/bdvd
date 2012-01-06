

#include "FileWriter.h"


FileWriter::FileWriter()
{
}

FileWriter::~FileWriter(){}

/**
 * Given a vtkPolyData and file name, writes that data to a vtk file with that file name.
 * The file is a binary vtk polydata  file.
 *
 * @param  vpd  the polydata object with the data to save
 * @param  fname  the filename to save the file with.
 * @return the error code from the file writer.
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
 * @param  fileName The file name to read.
 * @return NULL if the file isn't a valid polydata file or the
 *         vtkPolyData if the file is a vtk polydata file.
 */
vtkSmartPointer<vtkPolyData> FileWriter::ReadIsoSurfacePolyData(const char *fileName)
{
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(fileName);
	if (!reader->IsFilePolyData()) return NULL;
	reader->Update();
	vtkPolyData *data = reader->GetOutput();
	return data;
}

/**
 * Use the given renderwindow to save a screen shot in png format.
 *
 * @param renwin  the renderwindow to use.
 * @param fileName the filename to save it as.
 */
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


