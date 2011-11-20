#ifndef FILEWRITER_H
#define FILEWRITER_H



#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>

class FileWriter
{



public:
    FileWriter();
    int SaveIsoSurfacePolyData(vtkPolyData *, const char *);
};

#endif // FILEWRITER_H
