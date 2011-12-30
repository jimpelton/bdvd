#ifndef FILEWRITER_H
#define FILEWRITER_H



#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyDataReader.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkRenderWindow.h>

class FileWriter
{

public:
    FileWriter();
    ~FileWriter();
    int SaveIsoSurfacePolyData(vtkPolyData *data, const char * filename);
    vtkPolyData *ReadIsoSurfacePolyData( const char * filename);
    void SaveScreenShot(vtkRenderWindow *renwin, const char* filename);

    //void FileWriter::FileNameTimeString_MMDDHMS(char *timeName, int timeNameLength);
};

#endif // FILEWRITER_H
