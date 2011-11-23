#ifndef FILEWRITER_H
#define FILEWRITER_H



#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyDataReader.h>

class FileWriter
{

public:
    FileWriter();
    ~FileWriter();
    int SaveIsoSurfacePolyData(vtkPolyData *, const char *);
    vtkPolyData *ReadIsoSurfacePolyData( const char *);
};

#endif // FILEWRITER_H
