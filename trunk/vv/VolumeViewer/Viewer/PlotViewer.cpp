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

PlotViewer::PlotViewer(DataReaderFormat drf)
{
	m_drf = drf;
}
PlotViewer::PlotViewer(DataReaderFormat drv,
		vtkSmartPointer<vtkDataArray> xarr, vtkSmartPointer<vtkDataArray> yarr)
{

	if (xarr != NULL && yarr != NULL)
	{

	}
}
PlotViewer::~PlotViewer() {}

void PlotViewer::init(){}


/**
 *
 * @return 0 on failure, 1 on success.
 */
int PlotViewer::Setup()
{
	if (m_arrX == NULL || m_arrY == NULL){
		return 0;
	}

	view = vtkSmartPointer<vtkContextView>::New();

	table = vtkSmartPointer<vtkTable>::New();
	table->AddColumn(m_arrX);
	table->AddColumn(m_arrY);

	reader = ReaderFactory::GetReader(&m_drf);
	vtkPolyData *ppd = vtkPolyDataReader::SafeDownCast(reader)->GetOutput();

	std::map<double, long> bins;
	SurfaceUtil::TriangleAvgEdgeLength(ppd, &bins);
	table->SetNumberOfRows(bins.size());
	int row = 0;
	for(std::map<double,long>::iterator iter = bins.begin();
			iter != bins.end(); iter++)
	{
		vtkVariant avglength(iter->first);
		vtkVariant freq(iter->second);

		table->SetValue(row, 0, avglength);
		table->SetValue(row, 1, freq);

		row++;
	}
	table->Update();


	chart = vtkSmartPointer<vtkChartXY>::New();
	view->GetScene()->AddItem(chart);
	vtkPlot *line = chart->AddPlot(vtkChart::LINE);
	line->SetInput(table, 0, 1);
	line->SetColor(0, 255, 0, 255);
	line->SetWidth(2.0);

	view->Update();


	return 1;
}

vtkSmartPointer<vtkContextView> PlotViewer::GetView() const
{
    return view;
}

void PlotViewer::InitializeRenderer()
{
	fprintf(stdout, "PlotViewer::InitializeRenderer() is unimplemented.\n");
}

//void PlotViewer::setView(vtkSmartPointer<vtkContextView> view)
//{
//    this->view = view;
//}
