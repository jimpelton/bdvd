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


#include <vtkAlgorithmOutput.h>
#include <vtkAlgorithm.h>
#include <vtkPolyData.h>
#include <vtkVariant.h>
#include <vtkDataArray.h>
#include <vtkLongArray.h>
#include <vtkDoubleArray.h>


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



	TriangleEdgeLength();
	m_plotViewer->InitializeRenderer();
	InitializeRenderer();

	return 0;
}

void PlotViewerMain::InitializeRenderer()
{
	m_plotViewer->GetView()->SetInteractor(plotVtkWidget->GetInteractor());
	plotVtkWidget->SetRenderWindow(m_plotViewer->GetView()->GetRenderWindow());
	//m_plotViewer->InitializeRenderer();
}



void PlotViewerMain::TriangleEdgeLength()
{
	vtkSmartPointer<vtkDataArray> x = vtkSmartPointer<vtkDoubleArray>::New();
	vtkSmartPointer<vtkDataArray> y = vtkSmartPointer<vtkLongArray>::New();
	m_plotViewer->SetXArray(x);
	m_plotViewer->SetYArray(y);

	if (m_plotViewer->Setup()){
		fprintf(stdout, "PlotViewerMain::TriangleEdgeLength(): Setup failed!\n");
		return;
	}

	vtkSmartPointer<vtkTable> tbl = m_plotViewer->GetTable();


	vtkSmartPointer<vtkAlgorithm> vao = ReaderFactory::GetReader(&m_drf);
	vtkSmartPointer<vtkPolyData> pd = SurfaceUtil::ExtractSingleIsoSurface(vao->GetOutputPort(), 100, 0);

	std::map<double,long> bins;
	SurfaceUtil::TriangleAvgEdgeLength(pd, &bins);


	tbl->SetNumberOfRows(bins.size());
	int row = 0;
	for (std::map<double,long>::iterator iter = bins.begin(); iter != bins.end(); iter++)
	{
		vtkVariant dubskie = (*iter).first;
		vtkVariant lngskie = (*iter).second;
		tbl->SetValue(row, 0, dubskie);
		tbl->SetValue(row, 1, lngskie);
		row++;
	}
}
