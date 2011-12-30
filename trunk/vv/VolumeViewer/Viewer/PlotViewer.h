/*
 * PlotViewer.h
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 */

#ifndef PLOTVIEWER_H_
#define PLOTVIEWER_H_


#include "ReaderFactory.h"

#include <vtkDataArray.h>
#include <vtkSmartPointer.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkTable.h>


class PlotViewer {

private:

	vtkSmartPointer<vtkContextView> view;
	//vtkSmartPointer<vtkQtTableView> tableView;
	vtkSmartPointer<vtkTable> table;
	vtkSmartPointer<vtkDataArray> m_arrX;
	vtkSmartPointer<vtkDataArray> m_arrY;
	vtkSmartPointer<vtkChartXY> chart;
	vtkSmartPointer<vtkPlot> line;
	vtkSmartPointer<vtkAlgorithm> reader;

	DataReaderFormat m_drf;

	void init();

public:
	PlotViewer(DataReaderFormat drf);
	PlotViewer(DataReaderFormat drv,
			vtkSmartPointer<vtkDataArray> xarr, vtkSmartPointer<vtkDataArray> yarr);


	~PlotViewer();

	int Setup();

    vtkSmartPointer<vtkContextView> GetView() const;
    void setView(vtkSmartPointer<vtkContextView> view);


    void InitializeRenderer();
};

#endif /* PLOTVIEWER_H_ */
