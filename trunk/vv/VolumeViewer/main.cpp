
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
#include "ViewerOptions.h"

#include <QtGui/QApplication>
#include <stdlib.h>
#include <string>
#include <math.h>


void printUsage(char *extraMessage = NULL)
{
    char *s = 
        "VolumeViewer Usage\n" \
        "\tVolumeViewer [options] --polyfile <file-name>\n" \
        "\tVolumeViewer [options] --bmpprefix <file-prefix> [extractOptions]\n" \

        "[options]:\n" \
        "\t\t --vol [--isoval]" \

        "[extractOptions]:\n" \
        "\t\t--xsize <size> --ysize <size>\n" \
        "\t\t--imgstart --imgend [--use8bit]\n\n" \


        "\tNote: <file-prefix> is an absolute path plus the common naming of each file at that path.\n" \
        "\tExample: --bmpprefix C:\\data\\fetus\\fetus.bmp where each bmp file is appended with number.\n" \
        "";

    fprintf(stdout, "%s", s);
    if (extraMessage != NULL)
    {
        fprintf(stdout, "\n\n %s", s);
    }
}

int main(int argc, char* argv[])
{

	QApplication app(argc, argv);
	char *file;
	DataReaderFormat drf = {VV_READER_TYPE_NOT_SET, -1, -1, -1, -1, VV_BIG_ENDIAN, NULL, NULL, -1, -1, -1, 1};
	ViewerOptions viewOpts = {1, 0.0, 0.0, 0.0};

	if (argc > 1){
		int argcnt = 1;
		if (strcmp(argv[argcnt], "--help") == 0)
		{
			printUsage();
			return 0;
		}

		while (argcnt < argc){
			fprintf(stdout, "Reading commands...\n");
			if ( strcmp(argv[argcnt], "--polyfile")==0 )            //read a poly map
			{
				viewOpts.extractISOSurface = 0;
				drf.readerType = VV_POLY_DATA_READER;
				drf.fileName = argv[argcnt+1];
				drf.filePrefix = "unknown";
				argcnt+=2;
			}
			else if (strcmp(argv[argcnt], "--vol") == 0)           //read volume data
			{
				viewOpts.extractISOSurface = 0;
				argcnt+=1;

				if (strcmp(argv[argcnt], "--isoval") == 0)     //extract iso surface
				{
					viewOpts.extractISOSurface = 1;
					DEFAULT_ISO_VALUE = atoi(argv[argcnt+1]);
					argcnt+=2;
				}

				if (strcmp(argv[argcnt], "--bmpprefix") == 0) //vol data from bmp files.
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
		}
	}//if (argc>1)
	else
	{
		char *extraMessage = "Please specify at least --polyfile <file-name> or --bmpprefix <file-name> <options> [options] and the corresponding arguments.\n" \
				"If --bmpprefix you need at least --xsize, --ysize, --imgend, --imgstart.\n";
		printUsage(extraMessage);
		return 0;
	}

	drf.nSpacingX = 1;
	drf.nSpacingY = 1;
	drf.nSpacingZ = 1;
	drf.fileByteOrder = VV_BIG_ENDIAN;

	fprintf(stdout, "Starting GUI...\n");
	VVMain gui(drf, viewOpts);
	gui.InitializeRenderer();
	gui.show();
	app.exec();

	return 0;
}

