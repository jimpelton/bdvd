
// main.cpp: Defines the entry point for the console application.
//
// 
// 

#ifdef _WIN32
#include <Windows.h>
#endif


#include "VVMain.h"
#include "PlotViewerMain.h"
#include "DataReaderFormat.h"
#include "ViewerOptions.h"
#include "CLParser.h"
#include "Common.h"

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
        "\t\t[--isoval]\n" \

        "[extractOptions]:\n" \
        "\t\t--xsize <size> --ysize <size>\n" \
        "\t\t--imgstart --imgend [--use8bit]\n\n" \


        "\tNote: <file-prefix> is an absolute path plus the common naming of each file at that path.\n" \
        "\tExample: --bmpprefix C:\\data\\fetus\\fetus.bmp where each bmp file is appended with number.\n" \
        "";

    fprintf(stdout, "%s", s);
    if (extraMessage != NULL)
    {
        fprintf(stdout, "\n\n %s", extraMessage);
    }
}

int readerOptions(DataReaderFormat *drf)
{
	if (CLParser::ParseCL_s("bmpprefix", &(drf->filePrefix)))     //
	{
		drf->readerType = VV_MULTI_BMP_READER;
		drf->fileName = "unknown";

		if ( (CLParser::ParseCL_n("xsize",     &(drf->dimX))      &&
			  CLParser::ParseCL_n("ysize",   &(drf->dimY))        &&
			  CLParser::ParseCL_n("imgstart",&(drf->imgRngStart)) &&
			  CLParser::ParseCL_n("imgend",  &(drf->imgRngEnd)))  == false)
		{
			printUsage("Either xsize, ysize, imgstart or imgend was missing or malformed.\n");
			return 0;
		}
		CLParser::ParseCL_n("use8bit", &(drf->is8Bit));
	}
	return 1;
}

int main(int argc, char* argv[])
{

	QApplication app(argc, argv);
	char *file;

	DataReaderFormat drf = {VV_READER_TYPE_NOT_SET, -1, -1, -1, -1, VV_BIG_ENDIAN, NULL, NULL, -1, -1, -1, 1};
	ViewerOptions viewOpts = {1, 0.0, 0.0, 0.0};

	if (strcmp(argv[1], "--help") == 0)
	{
		printUsage();
		return 0;
	}

	int n;
	if (CLParser::Init(argc, argv) > 1)
	{
		fprintf(stdout, "Reading commands...\n");

		if (CLParser::ParseCL_s("polyfile", &(drf.fileName)))    //render binary poly data
		{
			//drf.fileName = s;
			drf.readerType = VV_POLY_DATA_READER;
			drf.filePrefix = "unknown";
			viewOpts.extractISOSurface = 0;
		}
		else if (CLParser::ParseCL_n("isoval", &n))    //extract an isovalue.
		{
			viewOpts.extractISOSurface = 1;
			DEFAULT_ISO_VALUE = n;

			if (!readerOptions(&drf)) exit(0);
		}

		/*
		 * else if (CLParser::ParseCL_flag("volume"))
		 * {
		 *   ...
		 *   readerOptions(&drf);
		 * }
		 */
	}
	else
	{
		char *extraMessage = "Please specify at least --polyfile <file-name> or --bmpprefix <file-name> <options> [options] and the corresponding arguments.\n" \
				"If --bmpprefix you need at least --xsize, --ysize, --imgend, --imgstart.\n";
		printUsage(extraMessage);
		exit(0);
	}


	drf.nSpacingX = 1;
	drf.nSpacingY = 1;
	drf.nSpacingZ = 1;
	drf.fileByteOrder = VV_BIG_ENDIAN;

	fprintf(stdout, "Starting GUI...\n");
	//PlotViewerMain pvm(drf);
	//pvm.InitializeRenderer();
	//pvm.show();
	//app.exec();

	VVMain gui(drf, viewOpts);
	gui.InitializeRenderer();
	gui.show();
	app.exec();

	return 0;
}

