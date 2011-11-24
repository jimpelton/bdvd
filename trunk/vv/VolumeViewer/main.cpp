
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


void printUsage()
{
    char *s = 
        "VolumeViewer Usage\n" \
        "\tVolumeViewer --polyfile <file-name>\n" \
        "\tVolumeViewer --bmpprefix <file-prefix>\n" \
        "\t\t--xsize <size> --ysize <size> --zsize <size>\n" \
        "\t\t--imgstart --imgend --is8bit\n\n" \
        "\tNote: <file-prefix> is an absolute path plus the common naming of each file at that path.\n" \
        "\tExample: --bmpprefix C:\data\fetus\fetus.bmp where each bmp file is appended with number.\n" \
        "";

    fprintf(stdout, "%s", s);
}

int main(int argc, char* argv[])
{

        QApplication app(argc, argv);
        char *file;
        DataReaderFormat drf;

        if (argc > 1){
            int argcnt = 1;
            if (strcmp(argv[argcnt], "--help") == 0)
            {
                printUsage();
                return 0;
            }
            while (argcnt < argc){
                
                if ( strcmp(argv[argcnt], "--polyfile")==0 )
                {
                    drf.readerType = VV_POLY_DATA_READER;
                    drf.fileName = argv[argcnt+1];
                    drf.filePrefix = "unknown";
                    argcnt+=2;
                }
                else if (strcmp(argv[argcnt], "--bmpprefix") == 0)
                {
                    drf.readerType = VV_MULTI_BMP_READER;
                    drf.filePrefix = argv[argcnt+1];
                    drf.fileName = "unknown";
                    argcnt+=2;
                    
                    int bmpArgsCnt = 0;
                    while (argcnt < argc)
                    {
                        if (strcmp(argv[argcnt], "--xsize") == 0)
                        {
                            drf.dimX = atoi(argv[argcnt+1]);
                            argcnt+=2; bmpArgsCnt++;
                        }
                        else if (strcmp(argv[argcnt], "--ysize") == 0)
                        {
                            drf.dimY = atoi(argv[argcnt+1]);
                            argcnt+=2; bmpArgsCnt++;
                        }
                        
                        else if (strcmp(argv[argcnt], "--imgend") == 0)
                        {
                            drf.imgRngEnd = atoi(argv[argcnt+1]);
                            argcnt+=2; bmpArgsCnt++;
                        }
                        else if (strcmp(argv[argcnt], "--imgstart") == 0)
                        {
                            drf.imgRngStart = atoi(argv[argcnt+1]);
                            argcnt+=2;  bmpArgsCnt++;
                        }
                        else if (strcmp(argv[argcnt], "--use8bit") == 0)
                        {
                            drf.is8Bit = 1;
                            argcnt += 1; bmpArgsCnt++;
                        }
                    }
                }
            }
            drf.nSpacingX = 1;
            drf.nSpacingY = 1;
            drf.nSpacingZ = 1;
            drf.fileByteOrder = VV_BIG_ENDIAN;
        }
        else
        {
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
        gui.InitializeRenderer();
        gui.show();
        app.exec();

    	return 0;
}

