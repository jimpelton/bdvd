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

PlotViewer::PlotViewer(DataReaderFormat drf, int screenWidth, int screenHeight) :
	Viewer(drf, screenWidth, screenHeight) {}

PlotViewer::PlotViewer(DataReaderFormat drf, int screenWidth, int screenHeight,
		vtkSmartPointer<vtkDataArray> xarr, vtkSmartPointer<vtkDataArray> yarr) :
		Viewer(drf, screenWidth, screenHeight)
{
	if (xarr != NULL && yarr != NULL)
	{
		m_arrX = xarr;
		m_arrY = yarr;
	}
}


PlotViewer::~PlotViewer() {}


int PlotViewer::Setup()
{
	if (m_arrX == NULL || m_arrY == NULL){
		return 0;
	}

	view = vtkSmartPointer<vtkContextView>::New();

	table = vtkSmartPointer<vtkTable>::New();
	table->AddColumn(m_arrX);
	table->AddColumn(m_arrY);
	table->SetNumberOfRows(m_arrX->GetNumberOfComponents());

	//reader = ReaderFactory::GetReader(&m_readerFormat);
	//vtkPolyData *ppd = vtkPolyDataReader::SafeDownCast(reader)->GetOutput();




	return 1;
}


void PlotViewer::InitializeRenderer()
{
	table->Update();


		chart = vtkSmartPointer<vtkChartXY>::New();
		view->GetScene()->AddItem(chart);
		vtkPlot *line = chart->AddPlot(vtkChart::LINE);
		line->SetInput(table, 0, 1);
		line->SetColor(0, 255, 0, 255);
		line->SetWidth(2.0);

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



