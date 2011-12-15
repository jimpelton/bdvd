#include "FileWriter.h"

FileWriter::FileWriter()
{
}

FileWriter::~FileWriter(){}

/**
 * Given a vtkPolyData and file name, writes that data to a vtk file with that file name.
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

int FileWriter::SaveScreenShot(vtkRenderWindow *renwin, const char *fileName)
{
	vtkWindowToImageFilter *windowToImageFilter = vtkWindowToImageFilter::New();
	  windowToImageFilter->SetInput(renwin);
	  windowToImageFilter->SetMagnification(3); //set the resolution of the output image (3 times the current resolution of vtk render window)
	  windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
	  windowToImageFilter->Update();

	  vtkPNGWriter *writer = vtkPNGWriter::New();
	  writer->SetFileName(fileName);
	  writer->SetInput(windowToImageFilter->GetOutput());
	  writer->Write();

	  windowToImageFilter->Delete();
	  writer->Delete();

}
