/*
 * PlotViewer.cpp
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 */

#include "PlotViewer.h"
#include "SurfaceUtil.h"

#include <vtkVariant.h>
#include <map>

PlotViewer::PlotViewer(DataReaderFormat drf,int screenWidth, int screenHeight) :
	Viewer(drf, screenWidth, screenHeight), m_numComponents(0), m_chartType(0) {}

PlotViewer::PlotViewer(DataReaderFormat drf, int screenWidth, int screenHeight,
		vtkSmartPointer<vtkDataArray> xarr, vtkSmartPointer<vtkDataArray> yarr) :
		Viewer(drf, screenWidth, screenHeight), m_numComponents(0), m_chartType(0)
{
		m_arrX = xarr;
		m_arrY = yarr;
}


PlotViewer::~PlotViewer() {}


int PlotViewer::Setup()
{
	view = vtkSmartPointer<vtkContextView>::New();
	table = vtkSmartPointer<vtkTable>::New();

	if (m_arrX == NULL || m_arrY == NULL){
		fprintf(stdout, "PlotViewer::Setup(): Arrays where null, you should call SetXArray()/SetYArray() before Setup().\n");
		return 0;
	}

	if (m_numComponents == 0){
		fprintf(stdout, "PlotViewer::Setup(): Please set the number of components by calling PlotViewer::SetNumberOfComponents(int).\n");
	}

	m_arrX->SetName(m_nameX);
	m_arrY->SetName(m_nameY);

	table->AddColumn(m_arrX);
	table->AddColumn(m_arrY);
	table->SetNumberOfRows(m_numComponents);

	return 1;
}


void PlotViewer::InitializeRenderer()
{
	if (m_arrX->GetNumberOfComponents() == 0 || m_arrY->GetNumberOfComponents() == 0){
		fprintf(stdout, "PlotViewer::InitializeRenderer(): Array components are 0 length, you should add data to the table before calling this method\n");
		return;
	}

	table->Update();
	chart = vtkSmartPointer<vtkChartXY>::New();
	view->GetScene()->AddItem(chart);
	vtkPlot *plot1 = chart->AddPlot(m_chartType);
	plot1->SetInput(table, 0, 1);
	plot1->SetColor(0, 255, 0, 255);
	plot1->SetWidth(1.0);

	view->Update();
}

void PlotViewer::Refresh() {}

vtkSmartPointer<vtkContextView> PlotViewer::GetView() const
{
    return view;
}

vtkSmartPointer<vtkTable> PlotViewer::GetTable() const
{
	return table;
}

void PlotViewer::SetXArray(vtkSmartPointer<vtkDataArray> arrX)
{
	m_arrX = arrX;
}

void PlotViewer::SetYArray(vtkSmartPointer<vtkDataArray> arrY)
{
	m_arrY = arrY;
}

void PlotViewer::SetNumComponents(int n)
{
	m_numComponents = n;
}

void PlotViewer::SetRowValue(vtkIdType row, vtkIdType col, vtkVariant val)
{
	table->SetValue(row, col, val);
}

void PlotViewer::SetXName(char *str)
{
	m_nameX = str;
}

void PlotViewer::SetYName(char *str)
{
	m_nameY = str;
}

void PlotViewer::SetChartType(int type)
{
	m_chartType = type;
}
