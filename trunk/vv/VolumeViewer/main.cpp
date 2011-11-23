
// main.cpp: Defines the entry point for the console application.
//
// 
// 

#ifdef _WIN32
#include <Windows.h>
#endif

#include "Common.h"
#include "VVMain.h"
#include "DataReaderFormat.h"

#include <QtGui/QApplication>
#include <string>
#include <math.h>


void parseCMD(int argc, char *argv[])
{

}



int main(int argc, char* argv[])
{

        QApplication app(argc, argv);
        char *file;
        DataReaderFormat drf;

        if (argc > 1){
            int argcnt = 1;
            if ( strcmp(argv[argcnt], "--polyfile") ){
                drf.readerType = VV_POLY_DATA_READER;
                drf.fileName = argv[argcnt+1];
                drf.filePrefix = "unknown";
            }

        }else{
            drf.readerType = VV_MULTI_BMP_READER;
            drf.filePrefix = "./data/fetus/fetus-00-2_3.5um__rec_voi.bmp";
            drf.fileName = "unknown";
            //drf.filePrefix = "./data/embryo/embryo-00-3_3.5um__rec_voi.bmp";
            drf.fileByteOrder = VV_BIG_ENDIAN;

            drf.imgRngStart = 1;
            drf.imgRngEnd = 350;
            drf.dimX = 569;
            drf.dimY = 595;

            drf.nSpacingX = 1;
            drf.nSpacingY = 1;
            drf.nSpacingZ = 1;

            drf.is8Bit = 1;
        }
            
        VVMain gui(drf);
        gui.show();
        app.exec();

    	return 0;
}

