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
#include <vtkPolyDataAlgorithm.h>
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

	PlotTriangleEdgeLength();
	m_plotViewer->InitializeRenderer();
	InitializePlotViewer();

	return 0;
}



void PlotViewerMain::InitializePlotViewer()
{
	m_plotViewer->GetView()->SetInteractor(plotVtkWidget->GetInteractor());
	plotVtkWidget->SetRenderWindow(m_plotViewer->GetView()->GetRenderWindow());
}

/**
 *
 * @return 1 on success 0 on failure
 */
int PlotViewerMain::PlotTriangleEdgeLength()
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
	m_plotViewer->SetXArray(x);
	m_plotViewer->SetYArray(y);
	m_plotViewer->SetXName("edge_length");
	m_plotViewer->SetYName("freq");
	m_plotViewer->SetNumComponents(bins.size());

	if (!m_plotViewer->Setup()){
		fprintf(stdout, "PlotViewerMain::TriangleEdgeLength(): Setup of the PlotViewer object failed!\n");
		return 0;
	}

	int row = 0;
	for (std::map<double,long>::iterator iter = bins.begin(); iter != bins.end(); iter++)
	{
		vtkVariant dubskie = (*iter).first;
		vtkVariant lngskie = (*iter).second;
		m_plotViewer->SetRowValue(row, 0, dubskie);
		m_plotViewer->SetRowValue(row, 1, lngskie);
		row++;
	}
	return 1;
}
