/********************************************************************
	created:	19:10:2011   11:36
	filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer\DataReaderFormat.h
	file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer
	file base:	DataReaderFormat
	file ext:	h
	author:		jim
	
	purpose:	
*********************************************************************/

#ifndef DATAREADERFORMAT_H
#define DATAREADERFORMAT_H


enum DataReaderType
{
	VV_VOLUME_16_READER, 
    STRUCTURED_POINTS_READER, 
    VV_RAW_IMG_READER, 
    VV_MULTI_BMP_READER,
    VV_POLY_DATA_READER
};

enum ByteOrderType
{
	VV_BIG_ENDIAN = 0, VV_LITTLE_ENDIAN
}; 

struct DataReaderFormat
{
	DataReaderType readerType;
	int dimX;
	int dimY;
	int imgRngStart;
	int imgRngEnd;
	ByteOrderType fileByteOrder;
    char * filePrefix;
	char * fileName;
	int nSpacingX;
	int nSpacingY;
	int nSpacingZ;
	int is8Bit;
};

#endif