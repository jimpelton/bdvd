#include <vtkRenderer.h>
#include <vtkIntArray.h>
#include <vtkDoubleArray.h>
#include <vtkPolyDataReader.h>
#include <vtkTriangle.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkContextScene.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkPolyData.h>
//#include <vtkLegendBoxActor.h>
//#include <vtkLine.h>
#include <vtkChartLegend.h>
#include <vtkAxis.h>

#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>

#include <SurfaceUtil.h>
#include <FileWriter.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

vector<QString*> *directory;
vector<string> *legendtexts;

char *title = "Avg. Triangle Edge Length per Iso Value";

struct rgba{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

const rgba colors[] =
{       {255, 0, 0, 255},
		{0, 255, 0, 255},
		{0, 0, 255, 255},
		{255,0,255, 255},
		{0,255,255, 255},
		{255,255,0, 255}
};


#define X_AXIS 1
#define Y_AXIS 0

MainWindow::MainWindow(vector<QString*>* dirs, vector<string>* lgnd, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    directory = dirs;
    legendtexts = lgnd;

    setup();
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::setup()
{

    VTKCREATE(vtkContextView, view);
    view->SetInteractor(ui->widget->GetInteractor());
    ui->widget->SetRenderWindow(view->GetRenderWindow());
    vtkSmartPointer<vtkChartXY> chart = vtkSmartPointer<vtkChartXY>::New();
    view->GetScene()->AddItem(chart);


    VTKCREATE(vtkTable, table);
    VTKCREATE(vtkIntArray, arrX);
    arrX->SetName("ISO Values");
    table->AddColumn(arrX);

    for (size_t i = 0; i < directory->size(); ++i)
    {
        VTKCREATE(vtkDoubleArray, arrArea);
        arrArea->SetName(legendtexts->at(i).c_str());
        table->AddColumn(arrArea);
    }

    int numPts = 255-68;
    table->SetNumberOfRows(numPts);

    VTKCREATE(vtkPolyDataReader, reader);
    QRegExp regex("^iso([0-9]+)");
    for (size_t dcount = 0; dcount < directory->size(); dcount++) {

        fprintf(stdout, "%d: Begining directory: %s\n", dcount, directory->at(dcount)->toAscii().data());

        QFileInfoList list = fileNames(directory->at(dcount));
        for (int fcount = 0; fcount < list.size(); fcount++){
            QFileInfo fileInfo = list.at(fcount);
            QString name = fileInfo.fileName();

            fprintf(stdout, "   %d: Processing file: %s\n", fcount, name.toAscii().data());

            int in = regex.indexIn(name);
            if (in != 0){
                fprintf(stdout, "%s is missing required \"isoXXX\" at front, skipping.\n", name.toStdString().c_str());
                continue;
            }

            bool res=false;
            QString strIso = regex.cap(1);
            int nIso = strIso.toInt(&res, 10);
            if (!res){
                fprintf(stdout, "Couldn't extract iso value %s from file name %s, skipping.\n",
                        strIso.toStdString().c_str(),
                        name.toStdString().c_str());
                continue;
            }
            if (fileInfo.suffix().compare("vtk") != 0) {
                fprintf(stdout, "%s does not have a .vtk suffix, skipping.\n", name.toStdString().c_str());
                continue;
            }

            reader->SetFileName(fileInfo.absoluteFilePath().toAscii().data());
            reader->Update();
            if (!reader->IsFilePolyData()) {
                fprintf(stdout, "%s is not a polydata file, skipping.\n", name.toStdString().c_str());
                continue;
            }

            //double area = SurfaceUtil::SurfaceArea(reader->GetOutput());
            double avgEdgeLength = SurfaceUtil::TriangleAvgEdgeLength(reader->GetOutput());
            table->SetValue(fcount, dcount+1, avgEdgeLength);
            table->SetValue(fcount, 0, nIso);
        }
        table->Update();

        vtkPlot *line = chart->AddPlot(vtkChart::LINE);
        line->SetInput(table, 0, dcount+1);
        line->SetColor(colors[dcount].r, colors[dcount].g, colors[dcount].b, colors[dcount].a);
    }

	chart->SetShowLegend(true);
	chart->GetLegend()->SetInline(false);
	chart->GetLegend()->SetHorizontalAlignment(vtkChartLegend::RIGHT);
	chart->GetLegend()->SetVerticalAlignment(vtkChartLegend::TOP);
	chart->GetLegend()->GetLabelProperties()->SetFontFamilyToTimes();
	chart->GetAxis(X_AXIS)->SetTitle("Iso Value");
	chart->GetAxis(Y_AXIS)->SetTitle("Avg. Edge Length");
	chart->SetTitle(title);

    view->Update();
}


QFileInfoList MainWindow::fileNames(QString *d)
{
    QDir dir;
    dir.setPath(*d);
    //if (!dir.exists()){ fprintf(stdout, "Directory %s don't exist much.\n", d->toAscii().data()); return ;}
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    return dir.entryInfoList();
}
