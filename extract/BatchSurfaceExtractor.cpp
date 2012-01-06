/*
 * SurfaceExtractor.cpp
 *
 *  Created on: Dec 19, 2011
 *      Author: jim
 */


#include "BatchSurfaceExtractor.h"

#include <SurfaceUtil.h>
#include <string>
#include <sstream>
#include <iomanip>

BatchSurfaceExtractor::BatchSurfaceExtractor(DataReaderFormat drf, int *isoVals, int numIsoVals, char *outpath)
    : m_drf(drf), m_isoVals(isoVals), m_numIsoVals(numIsoVals), m_outpath(outpath)
{
    insideOut =1 ;
}

BatchSurfaceExtractor::~BatchSurfaceExtractor()
{}

void BatchSurfaceExtractor::makeReader()
{
    reader = vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFilePrefix(m_drf.filePrefix);

    reader->SetAllow8BitBMP(1);

    reader->SetFileNameSliceOffset(0);
    reader->SetDataExtent( 0, m_drf.dimX,
                           0, m_drf.dimY,
                           m_drf.imgRngStart,
                           m_drf.imgRngEnd);

    reader->SetDataOrigin(0.,0.,0.);
    reader->SetDataScalarTypeToUnsignedChar();
    reader->SetDataByteOrderToBigEndian();
}

void BatchSurfaceExtractor::DoExtract()
{
	makeReader();
	SurfaceUtil::BatchExtractAndSaveIsoSurface(reader->GetOutputPort(), m_isoVals, m_numIsoVals, m_drf.fileName, m_outpath);
}
