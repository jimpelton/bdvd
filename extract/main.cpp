/*
 * main.cpp
 *
 *  Created on: Dec 19, 2011
 *      Author: jim
 */



#include "BatchSurfaceExtractor.h"
#include <DataReaderFormat.h>
#include <CLParser.h>

#include <cstdlib>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

DataReaderFormat drf ;
int isostart;
int isoend;
bool ready;
char *outpath;

void parse_cmd_line(int argc, char *argv[])
{
	ready = true;
	CLParser::Init(argc, argv);
	if (!CLParser::ParseCL_n("dimx",      &(drf.dimX)))       { cout << "Need dimX\n";      ready=false; }
	if (!CLParser::ParseCL_n("dimy",      &(drf.dimY)))       { cout << "Need dimY\n";      ready=false; }
	if (!CLParser::ParseCL_n("imgstart",  &(drf.imgRngStart))){ cout << "Need imgstart\n";  ready=false; }
	if (!CLParser::ParseCL_n("imgend",    &(drf.imgRngEnd)))  { cout << "Need imgend\n";    ready=false; }
	if (!CLParser::ParseCL_s("bmpprefix", &(drf.filePrefix))) { cout << "Need bmpprefix\n"; ready=false; }
	if (!CLParser::ParseCL_s("fileprefix",&(drf.fileName)))   { cout << "Need fileprefix\n";ready=false; }
	if (!CLParser::ParseCL_n("isostart",  &isostart))         { cout << "Need isostart\n";  ready=false; }
	if (!CLParser::ParseCL_n("isoend",    &isoend))           { cout << "Need isoend\n";    ready=false; }
	if (!CLParser::ParseCL_s("outpath",   &outpath))          { cout << "Need outpath\n";   ready=false; }

	if (CLParser::ParseCL_flag("saveData"))
	{

	}

	if (isoend < isostart){ cout << "isoend value < isostart value! Fix it please.\n"; ready=false; }

	if (ready){
		cout << "Using these options:\n";
		cout << "\t dimX: "        << drf.dimX << endl;
		cout << "\t dimY: "        << drf.dimY<< endl;
		cout << "\t imgstart: "    << drf.imgRngStart << endl;
		cout << "\t imgend: "      << drf.imgRngEnd << endl;
		cout << "\t bmpprefix: "   << drf.filePrefix << endl;
		cout << "\t fileprefix: "  << drf.fileName << endl;
		cout << "\t isostart: "    << isostart << endl;
		cout << "\t isoend: "      << isoend << endl;
		cout << "\t ready: "       << ready << endl;
		cout << "\t outpath: "     << outpath << endl;
	}
}

int main(int argc, char *argv[])
{

	drf.readerType = VV_MULTI_BMP_READER;
	drf.fileByteOrder = VV_BIG_ENDIAN;
	drf.nSpacingX = drf.nSpacingY = drf.nSpacingZ = 1;
	drf.is8Bit = 1;

	parse_cmd_line(argc, argv);

	if (!ready){ cout << "\nCheck yo args foo!\n"; exit(0); }


    int ivalues[isoend-isostart];
    for (int i = isostart; i <= isoend; ++i)
    {
    	ivalues[i-isostart] = i;
    }
    int numiv = sizeof(ivalues)/sizeof(int);
    BatchSurfaceExtractor bse(drf, ivalues, numiv, outpath);


    bse.DoExtract();



    return 0;
}

//drf.readerType = VV_MULTI_BMP_READER;
////drf.dimX = 569;
////drf.dimY = 595;
////drf.imgRngStart = 1;
////drf.imgRngEnd = 350;
//drf.fileByteOrder = VV_BIG_ENDIAN;
//drf.nSpacingX = drf.nSpacingY = drf.nSpacingZ = 1;
//drf.is8Bit = 1;
//drf.filePrefix = "/home/jim/s/programming/data/oxford/CS-Embryo-00-2_3.5um/skull_569x595x351_rename/fetus-00-2_3.5um__rec_voi.bmp";
//drf.fileName = "fetus-00-2_3.5um__rec_voi.bmp";

//	DataReaderFormat drf ;
//	drf.readerType = VV_MULTI_BMP_READER;
//	drf.dimX = 525;
//	drf.dimY = 626;
//	drf.imgRngStart = 1;
//	drf.imgRngEnd = 356;
//	drf.fileByteOrder = VV_BIG_ENDIAN;
//	drf.nSpacingX = drf.nSpacingY = drf.nSpacingZ = 1;
//	drf.is8Bit = 1;
//	drf.filePrefix = "/home/jim/s/programming/data/oxford/CS-Embryo-00-3_3.5um/skull_525x626x356_rename/embryo-00-3_3.5um__rec_voi.bmp";
//	drf.fileName = "embryo-00-3_3.5um__rec_voi.bmp";

//	DataReaderFormat drf ;
//	drf.readerType = VV_MULTI_BMP_READER;
//	drf.dimX = 592;
//	drf.dimY = 584;
//	drf.imgRngStart = 1;
//	drf.imgRngEnd = 348;
//	drf.fileByteOrder = VV_BIG_ENDIAN;
//	drf.nSpacingX = drf.nSpacingY = drf.nSpacingZ = 1;
//	drf.is8Bit = 1;
//	drf.filePrefix = "/home/jim/s/programming/data/oxford/CS-Embryo-05-05_3.6um/skull_592x584x348_rename/embryo-05-05_3.6um__rec_voi.bmp";
//	drf.fileName = "embryo-05-05_3.6um__rec_voi.bmp";

//	DataReaderFormat drf ;
//	drf.readerType = VV_MULTI_BMP_READER;
//	drf.dimX = 844;
//	drf.dimY = 665;
//	drf.imgRngStart = 1;
//	drf.imgRngEnd = 433;
//	drf.fileByteOrder = VV_BIG_ENDIAN;
//	drf.nSpacingX = drf.nSpacingY = drf.nSpacingZ = 1;
//	drf.is8Bit = 1;
//	drf.filePrefix = "/home/jim/s/programming/data/oxford/CS-Embryo-05-06_3.5um/skull_844x665x433_rename/05-06_3.5um__rec_voi.bmp";
//	drf.fileName = "05-06_3.5um__rec_voi.bmp";

