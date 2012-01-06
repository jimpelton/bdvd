#ifndef FILEWRITER_H
#define FILEWRITER_H



#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyDataReader.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

class FileWriter
{

public:
    FileWriter();
    ~FileWriter();
    int SaveIsoSurfacePolyData(vtkPolyData *data, const char * filename);
    vtkSmartPointer<vtkPolyData> ReadIsoSurfacePolyData( const char * filename);
    void SaveScreenShot(vtkRenderWindow *renwin, const char* filename);

};

#endif // FILEWRITER_H
