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
	Viewer(drf, screenWidth, screenHeight), m_numComponents(0)
{
	//allComponentsSet = 0x00;
}

//PlotViewer::PlotViewer(DataReaderFormat drf, int screenWidth, int screenHeight,
//		vtkSmartPointer<vtkDataArray> xarr, vtkSmartPointer<vtkDataArray> yarr) :
//		Viewer(drf, screenWidth, screenHeight), m_numComponents(0), m_chartType(0)
//{
//		m_arrX = xarr;
//
//}


PlotViewer::~PlotViewer()
{}

/**
 * Add all the columns, check the sizes, set number of rows.
 * @return
 */
int PlotViewer::Setup()
{
	view = vtkSmartPointer<vtkContextView>::New();
	table = vtkSmartPointer<vtkTable>::New();


	if (m_arrX == NULL || m_yArrays.size() == 0){
		fprintf(stdout, "PlotViewer::Setup(): Arrays where null, you should call SetXArray()/SetYArray() before Setup().\n");
		return 0;
	}

	if (m_numComponents == 0){
		fprintf(stdout, "PlotViewer::Setup(): Please set the number of components by calling PlotViewer::SetNumberOfComponents(int).\n");
	}

	table->AddColumn(m_arrX);

	std::vector<vtkSmartPointer<vtkDataArray> >::iterator iter;
	for (iter= m_yArrays.begin(); iter != m_yArrays.end(); ++iter)
	{
		table->AddColumn(*iter);
	}

	table->SetNumberOfRows(m_numComponents);

	return 1;
}


void PlotViewer::InitializeRenderer()
{
	if (m_arrX->GetNumberOfComponents() == 0){
		fprintf(stdout, "PlotViewer::InitializeRenderer(): Array components are 0 length, you should add data to the table before calling this method\n");
		return;
	}

	table->Update();
	chart = vtkSmartPointer<vtkChartXY>::New();
	view->GetScene()->AddItem(chart);

	for (size_t i = 0; i < m_plots.size(); i++)
	{
		plot p = m_plots.at(i);
		vtkPlot *plot1 = chart->AddPlot(p.type);
		plot1->SetInput(table, 0, i+1);
		plot1->SetColor(p.r, p.g, p.b, p.a);
		plot1->SetWidth(1.0);
	}
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

void PlotViewer::SetXArray(vtkSmartPointer<vtkDataArray> arrX, char *arrName)
{
	m_arrX = arrX;
	m_arrX->SetName(arrName);
}

/**
 * Add an array for Y-Axis set of values to the chart.
 * @param arrY
 */
void PlotViewer::AddYArray(vtkSmartPointer<vtkDataArray> arrY, char *arrName, plot *p)
{
	arrY->SetName(arrName);
	m_yArrays.push_back(arrY);
	m_plots.push_back(*p);
}

void PlotViewer::SetNumComponents(int n)
{
	m_numComponents = n;
	//allComponentsSet |= NUM_COMPONENTS_SET;
}


/**
 * Add a value that will be plotted.
 * @param row
 * @param col
 * @param val
 */
void PlotViewer::SetRowValue(vtkIdType row, vtkIdType col, vtkVariant val)
{
	table->SetValue(row, col, val);
	//allComponentsSet |= ROW_VALUE_SET;
}


