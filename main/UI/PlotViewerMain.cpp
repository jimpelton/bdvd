/*
 * PlotViewerMain.cpp
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 *
 *      purpose: holds business logic for displaying the output of a PlotViewer.
 */

#include "PlotViewerMain.h"
#include "SurfaceUtil.h"
#include "ReaderFactory.h"
#include "FileWriter.h"


#include <vtkAlgorithmOutput.h>
#include <vtkAlgorithm.h>
#include <vtkPolyData.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkVariant.h>
#include <vtkDataArray.h>
#include <vtkLongArray.h>
#include <vtkDoubleArray.h>
#include <vtkChart.h>

#include <QDir>
#include <QString>
#include <QRegExp>



#include <map>

PlotViewerMain::PlotViewerMain(DataReaderFormat drf, ViewerOptions vopt) {
	m_vopt = vopt;
	m_drf = drf;
	Setup();
}

PlotViewerMain::~PlotViewerMain()
{
	delete m_plotViewer;
}

int PlotViewerMain::Setup()
{
	m_plotViewer = new PlotViewer(m_drf, 640, 480);
	this->SetupUi(this, m_drf);

	if (!choosePlot())
	{
		fprintf(stdout, "PlotViewerMain::Setup(): The plot couldn't be made.\n");
		return 0;
	}
	InitializePlotViewer();

	return 1;
}

void PlotViewerMain::InitializePlotViewer()
{
	m_plotViewer->InitializeRenderer();
	m_plotViewer->GetView()->SetInteractor(plotVtkWidget->GetInteractor());
	plotVtkWidget->SetRenderWindow(m_plotViewer->GetView()->GetRenderWindow());
}

int PlotViewerMain::choosePlot()
{
	int rval;
	switch(m_vopt.mode)
		{
		case OpMode::PLOT_VIEW_TRIANGLE_AVERAGES:
			rval = plotTriangleEdgeLength();
			break;
		case OpMode::PLOT_VIEW_SURFACE_AREAS:
			rval = plotSurfaceAreas();
			break;
		default:
			fprintf(stdout, "PlotViewerMain::choosePlot(): No plot given.\n");
			/* no break */
		}
	return rval;
}

/**
 * Make a plot of average triangle edge lengths from a ploydata file.
 * @return 1 on success 0 on failure
 */
int PlotViewerMain::plotTriangleEdgeLength()
{
	vtkSmartPointer<vtkAlgorithm> vao = ReaderFactory::GetReader(&m_drf);
	if (vao == NULL)
	{
		fprintf(stdout, "PlotViewerMain::TriangleEdgeLength(): The reader returned was null.\n");
		return 0;
	}
	vtkSmartPointer<vtkPolyDataReader> asdf = vtkPolyDataReader::SafeDownCast(vao);
	vtkSmartPointer<vtkPolyData> pd  = asdf->GetOutput();


	std::map<double,long> bins;
	SurfaceUtil::TriangleAvgEdgeLength(pd, &bins);

	vtkSmartPointer<vtkDataArray> x = vtkSmartPointer<vtkDoubleArray>::New();
	vtkSmartPointer<vtkDataArray> y = vtkSmartPointer<vtkLongArray>::New();
	m_plotViewer->SetXArray(x, "edge_length");
	plot p = {vtkChart::POINTS, 255, 0, 0, 255, "some name"};

	m_plotViewer->AddYArray(y, "freq", &p);
	m_plotViewer->SetNumComponents(bins.size());

	if (!m_plotViewer->Setup()){
		fprintf(stdout, "PlotViewerMain::TriangleEdgeLength(): Setup of the PlotViewer object failed!\n");
		return 0;
	}

	int row = 0;
	for (std::map<double,long>::iterator iter = bins.begin(); iter != bins.end(); iter++)
	{
		double dubskie = (*iter).first;
		long   lngskie = (*iter).second;
		m_plotViewer->SetRowValue(row, 0, dubskie);
		m_plotViewer->SetRowValue(row, 1, lngskie);
		row++;
	}
	return 1;
}

/**
 * Plot surface areas to iso values for all of the .vtk polyfiles in the dir.
 * @return 1 on success, 0 on failure.
 */
int PlotViewerMain::plotSurfaceAreas()
{
	QDir dir;
	dir.setPath(m_drf.filePrefix);
	if (!dir.exists())
	{
		fprintf(stdout, "The directory %s doesn't exist.\n", m_drf.filePrefix);
		return 0;
	}
	dir.setFilter(QDir::Files);
	dir.setSorting(QDir::Name);

	QFileInfoList list = dir.entryInfoList();

	vtkSmartPointer<vtkDataArray> x = vtkSmartPointer<vtkDoubleArray>::New();
	vtkSmartPointer<vtkDataArray> y = vtkSmartPointer<vtkLongArray>::New();
	vtkSmartPointer<vtkDataArray> y2 = vtkSmartPointer<vtkLongArray>::New();

	m_plotViewer->SetXArray(x, "iso");
	plot p =  {vtkChart::POINTS, 0, 255, 0, 255, "surface areas 1"};
	//plot p2 = {vtkChart::POINTS, 255, 0, 0, 255, "surface areas 2"};
	m_plotViewer->AddYArray(y, "area", &p);
	//m_plotViewer->AddYArray(y2, "area2", &p2);
	m_plotViewer->SetNumComponents(list.size());

	if (!m_plotViewer->Setup()){
		fprintf(stdout, "PlotViewerMain::plotSurfaceAreas(): Setup of the PlotViewer object failed!\n");
		return 0;
	}



	vtkSmartPointer<vtkPolyDataReader> asdf = vtkSmartPointer<vtkPolyDataReader>::New();
	QRegExp regex("^iso([0-9]+)");
	for (int i = 0; i < list.size(); ++i)
	{

		QFileInfo fileInfo = list.at(i);
		QString name = fileInfo.fileName();
		int in = regex.indexIn(name);
		if (in != 0){
			fprintf(stdout, "%s is missing required \"isoXXX\" at front, skipping.\n", name.toStdString().c_str());
			continue;
		}

		bool res=false;
		QString strIso = regex.cap(1);
		int nIso = strIso.toInt(&res, 10);
		if (!res){
			fprintf(stdout, "Couldn't extract iso value %s from file name %s, skipping.\n", strIso.toStdString().c_str(), name.toStdString().c_str());
			continue;
		}

		if (fileInfo.suffix().compare("vtk") != 0) {
			fprintf(stdout, "%s does not have a .vtk suffix, skipping.\n", name.toStdString().c_str());
			continue;
		}

		asdf->SetFileName(fileInfo.absoluteFilePath().toStdString().c_str());
		asdf->Update();
		if (!asdf->IsFilePolyData()) {
			fprintf(stdout, "%s is not a polydata file, skipping.\n", name.toStdString().c_str());
			continue;
		}


		double area = SurfaceUtil::SurfaceArea(asdf->GetOutput());
		m_plotViewer->SetRowValue(i, 0, nIso);
		m_plotViewer->SetRowValue(i, 1, area);
		fprintf(stdout, "Processed %s.\n", name.toStdString().c_str());
	}
	return 1;
}
















