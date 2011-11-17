#ifndef FILEWRITER_H
#define FILEWRITER_H



#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>

class FileWriter
{



public:
    FileWriter();


    int SaveIsoSurface(vtkPolyData *, char *);
};

#endif // FILEWRITER_H
