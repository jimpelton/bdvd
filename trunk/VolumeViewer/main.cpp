
// main.cpp: Defines the entry point for the console application.
//
// 
// 

#ifdef _WIN32
#include <Windows.h>
#endif

#include "Common.h"
#include "VVMain.h"

#include <QtGui/QApplication>
#include <string>
#include <math.h>


void parseCMD(char *argv[])
{

}



int main(int argc, char* argv[])
{

        QApplication app(argc, argv);

        VVMain gui;
        gui.show();
        app.exec();

	return 0;
}

