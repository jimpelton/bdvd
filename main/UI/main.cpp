
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
#include <qmainwindow.h>
#include <stdlib.h>
#include <string>
#include <math.h>

//////////Externed Globals from Common.h/////////////////////
int DEFAULT_SCREEN_WIDTH  = 640;   //rener window width
int DEFAULT_SCREEN_HEIGHT = 480;   //rener window height.

int DEFAULT_WINDOW_WIDTH = 1280;
int DEFAULT_WINDOW_HEIGHT = 720;

int DEFAULT_INITIAL_COLOR_RED   = 228;
int DEFAULT_INITIAL_COLOR_GREEN = 225;
int DEFAULT_INITIAL_COLOR_BLUE  = 216;
int DEFAULT_INITIAL_COLOR_ALPHA = 255;

int DEFAULT_INITIAL_ISO_SLIDER_MAX = 255;
int DEFAULT_INITIAL_ISO_SLIDER_MIN = 1;
int DEFAULT_ISO_VALUE = 55;
////////////////////////////////////////////////////////////


QMainWindow *gui = NULL;

int plotMode(char *);

void printUsage(char *extraMessage = NULL)
{
    char *s = 
        "VolumeViewer Usage\n" \
        "\tVolumeViewer [options] --surface <file-name>\n" \
        "\tVolumeViewer [options] --plots   <file-prefix> [extractOptions]\n" \

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

int readerOptions(DataReaderFormat *drf, ViewerOptions *viewOpts)
{
	if (CLParser::ParseCL_s("polyfile", &(drf->fileName)))    //render binary poly data
	{
		viewOpts->mode = OpMode::VIEW_POLYDATA;
		drf->readerType = VV_POLY_DATA_READER;
		drf->filePrefix = "unknown";
	}
	else if (CLParser::ParseCL_s("bmpprefix", &(drf->filePrefix)))     //
	{
		drf->readerType = VV_MULTI_BMP_READER;
		drf->fileName = "unknown";
		drf->nSpacingX = 1;
		drf->nSpacingY = 1;
		drf->nSpacingZ = 1;
		drf->fileByteOrder = VV_BIG_ENDIAN;

		if (CLParser::ParseCL_flag("use8bit")) drf->is8Bit = 1;

		if ( (CLParser::ParseCL_n("xsize",   &(drf->dimX))        &&
			  CLParser::ParseCL_n("ysize",   &(drf->dimY))        &&
			  CLParser::ParseCL_n("imgstart",&(drf->imgRngStart)) &&
			  CLParser::ParseCL_n("imgend",  &(drf->imgRngEnd)))  == false)
		{
			printUsage("Either xsize, ysize, imgstart or imgend was missing or malformed.\n");
			return 0;
		}
	}
	return 1;
}

int extractOptions(DataReaderFormat *drf, ViewerOptions *viewOpts)
{
	fprintf(stdout, "Extraction not supported right now. Exiting...\n");
	exit(0);
}

int plotsOptions(DataReaderFormat *drf, ViewerOptions *viewOpts)
{
	char *s;
	if (CLParser::ParseCL_s("type", &s))
	{
		viewOpts->mode = plotMode(s);
	}
	CLParser::ParseCL_s("polyfile",  &(drf->filePrefix));
	CLParser::ParseCL_s("outdir",   &(viewOpts->outDir));

	return 1;
}

int plotMode(char *s)
{
	std::string str = s;
	if (str.compare("TriangleAverageEdgeFreq")==0) return OpMode::PLOT_VIEW_TRIANGLE_AVERAGES;
	if (str.compare("BatchTriangleAverageEdgeFreq") == 0) return OpMode::PLOTS_BATCH_TRIANGLE_AVERAGES;
	if (str.compare("IsoValueSurfaceAreas") == 0)  return OpMode::PLOT_VIEW_SURFACE_AREAS;

	return OpMode::PLOT_VIEW_TRIANGLE_AVERAGES;
}

//TODO: plotsOptions() method to check plots specific options.
void parseCommandLine(int argc, char *argv[], DataReaderFormat *drf, ViewerOptions *viewOpts)
{
	int n;
	if (CLParser::Init(argc, argv) > 1)
	{
		fprintf(stdout, "Reading commands...\n");

		if (CLParser::ParseCL_flag("surface"))
		{
			if (CLParser::ParseCL_n("isoval", &n))              //extract an isovalue from vol data.
			{
				viewOpts->mode = OpMode::EXTRACT_AND_VIEW_SURFACE;
				DEFAULT_ISO_VALUE = n;

			}
			if (!readerOptions(drf,viewOpts)) exit(0);
		}//surface
		else if (CLParser::ParseCL_flag("extract"))
		{
			viewOpts->mode = OpMode::EXTRACT_BATCH;
			if (!readerOptions(drf, viewOpts)) exit(0);
			if (!extractOptions(drf,viewOpts)) exit(0);

		}
		else if (CLParser::ParseCL_flag("plots"))
		{
//			viewOpts->mode = OPMODE_PLOT_VIEW_TRIANGLE_AVERAGES;
			if (!readerOptions(drf, viewOpts)) exit(0);
			if (!plotsOptions(drf, viewOpts)) exit(0);
			gui = new PlotViewerMain(*drf, *viewOpts);
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
}

void cleanup()
{
    CLParser::CleanUp();
}

int main(int argc, char* argv[])
{

	QApplication app(argc, argv);
	char *file;

	DataReaderFormat drf = {VV_READER_TYPE_NOT_SET, -1, -1, -1, -1, VV_BIG_ENDIAN, -1, -1, -1, 1, "unknown", "unknown"};
	ViewerOptions viewOpts = {OpMode::EXTRACT_AND_VIEW_SURFACE, NULL};

	atexit(cleanup);

	parseCommandLine(argc, argv, &drf, &viewOpts);

	if (strcmp(argv[1], "--help") == 0)
	{
		printUsage();
		return 0;
	}

	fprintf(stdout, "Starting GUI...\n");

	if (gui == NULL) gui = new VVMain(drf, viewOpts);
	gui->show();
	app.exec();

	return 0;
}

