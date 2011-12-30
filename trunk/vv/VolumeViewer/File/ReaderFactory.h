/*
 * ReaderFactory.h
 *
 *  Created on: Dec 24, 2011
 *      Author: jim
 */



#ifndef READERFACTORY_H_
#define READERFACTORY_H_


#include "DataReaderFormat.h"

#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkBMPReader.h>
#include <vtkAlgorithm.h>

class ReaderFactory {
private:
	ReaderFactory();
	~ReaderFactory();

private:
	static vtkSmartPointer<vtkAlgorithm> makeMultiBMPReader(DataReaderFormat *drf);
	static vtkSmartPointer<vtkAlgorithm> makePolyDataReader(DataReaderFormat *drf);
	static vtkSmartPointer<vtkAlgorithm> makeV16Reader(DataReaderFormat *drf);
	static vtkSmartPointer<vtkAlgorithm> makeRawImgReader(DataReaderFormat *drf);


public:
	static vtkSmartPointer<vtkAlgorithm> GetReader(DataReaderFormat *drf);

};

#endif /* READERFACTORY_H_ */
