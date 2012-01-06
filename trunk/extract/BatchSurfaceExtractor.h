/*
 * SurfaceExtractor.h
 *
 *  Created on: Dec 19, 2011
 *      Author: jim
 */

#ifndef SURFACEEXTRACTOR_H_
#define SURFACEEXTRACTOR_H_

#include <DataReaderFormat.h>

#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkClipPolyData.h>
#include <vtkBox.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataWriter.h>


class BatchSurfaceExtractor {

private:

	DataReaderFormat m_drf;
	int insideOut;
	int * m_isoVals;
	int   m_numIsoVals;
	char *m_outpath;

	vtkSmartPointer<vtkBMPReader> reader;
	vtkSmartPointer<vtkMarchingCubes> mCubesExtractor;
	vtkSmartPointer<vtkPolyDataMapper> polyDataMapper;

private:
	void makeReader();
	void clip();

public:
    BatchSurfaceExtractor(DataReaderFormat drf, int *m_isoVals, int m_numIsoVals, char *outpath);
	virtual ~BatchSurfaceExtractor();


public:
	void DoExtract();

};

#endif /* SURFACEEXTRACTOR_H_ */
