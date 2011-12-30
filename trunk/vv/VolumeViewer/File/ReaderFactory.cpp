/*
 * ReaderFactory.cpp
 *
 *  Created on: Dec 24, 2011
 *      Author: jim
 *
 *
 *  Purpose: Static methods to create the correct reader based on
 *           information from a DataReaderFormat struct.
 *
 */

#include "ReaderFactory.h"

ReaderFactory::ReaderFactory() {
	// TODO Auto-generated constructor stub

}

ReaderFactory::~ReaderFactory() {
	// TODO Auto-generated destructor stub
}

/**
 * Get the proper reader for this DataReaderFormat. This method returns a vtkSmartPointer of vtkAlgorithm.
 * The vtkAlgorithm is guaranteed to be a reader from the vtk api.
 *
 * @param drf the reader format to match a reader to.
 * @return a vtkAlgorithm that is some kind of data source for a vtk pipeline.
 */
vtkSmartPointer<vtkAlgorithm> ReaderFactory::GetReader(DataReaderFormat *drf)
{
	vtkSmartPointer<vtkAlgorithm> rval = NULL;
	switch(drf->readerType)
	{
	case VV_MULTI_BMP_READER:
		rval = makeMultiBMPReader(drf);
		break;
	case VV_POLY_DATA_READER:
		rval = makePolyDataReader(drf);
		break;
	case VV_RAW_IMG_READER:
		rval = makeRawImgReader(drf);
		break;
	case VV_VOLUME_16_READER:
		rval = makeV16Reader(drf);
		break;
	default:
		break;
	}
	return rval;
}

vtkSmartPointer<vtkAlgorithm> ReaderFactory::makeMultiBMPReader (DataReaderFormat *drf)
{
    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFilePrefix(drf->filePrefix);
    reader->Update();
    int ecode = reader->GetErrorCode();
    if (ecode != 0){
        return NULL;
    }

    reader->SetAllow8BitBMP(drf->is8Bit);

    reader->SetFileNameSliceOffset(drf->imgRngStart );
    reader->SetDataExtent( 0, drf->dimX,
                           0, drf->dimY,
                           drf->imgRngStart, drf->imgRngEnd);

    reader->SetDataOrigin(0.,0.,0.);
    reader->SetDataScalarTypeToUnsignedChar();
    reader->SetDataByteOrderToBigEndian();

    return reader;
}

vtkSmartPointer<vtkAlgorithm> ReaderFactory::makePolyDataReader (DataReaderFormat *drf)
{
	vtkSmartPointer<vtkPolyDataReader> vpdr = vtkSmartPointer<vtkPolyDataReader>::New();
	vpdr->SetFileName(drf->fileName);
	vpdr->Update();
	if (!vpdr->IsFilePolyData()) return NULL;

	return vpdr;
}

vtkSmartPointer<vtkAlgorithm> ReaderFactory::makeV16Reader(DataReaderFormat *drf)
{
	return NULL;
}

vtkSmartPointer<vtkAlgorithm> ReaderFactory::makeRawImgReader(DataReaderFormat *drf)
{
	return NULL;
}
