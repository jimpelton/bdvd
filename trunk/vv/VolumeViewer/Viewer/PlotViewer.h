/*
 * PlotViewer.h
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 */

#ifndef PLOTVIEWER_H_
#define PLOTVIEWER_H_


#include "ReaderFactory.h"
#include "Viewer.h"

#include <vtkDataArray.h>
#include <vtkSmartPointer.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkTable.h>
#include <vtkType.h>
#include <vtkVariant.h>



class PlotViewer : Viewer {

private:

	vtkSmartPointer<vtkContextView> view;
	//vtkSmartPointer<vtkQtTableView> tableView;
	vtkSmartPointer<vtkTable> table;
	vtkSmartPointer<vtkDataArray> m_arrX;
	vtkSmartPointer<vtkDataArray> m_arrY;
	vtkSmartPointer<vtkChartXY> chart;
	vtkSmartPointer<vtkPlot> line;
	vtkSmartPointer<vtkAlgorithm> reader;

	char *m_nameX;
	char *m_nameY;

	int m_numComponents;

public:
	PlotViewer(DataReaderFormat drf, int screenWidth, int screenHeight);
	PlotViewer(DataReaderFormat drv, int screenWidth, int screenHeight,
			vtkSmartPointer<vtkDataArray> xarr, vtkSmartPointer<vtkDataArray> yarr);

	~PlotViewer();

	///////overrides from Viewer///////
	int Setup();
	void InitializeRenderer();
	void Refresh();


    vtkSmartPointer<vtkContextView> GetView() const;
    vtkSmartPointer<vtkTable> GetTable() const;

    void SetXArray(vtkSmartPointer<vtkDataArray> arrX);
    void SetYArray(vtkSmartPointer<vtkDataArray> arrY);
    void SetNumComponents(int n);
    void SetRowValue(vtkIdType, vtkIdType, vtkVariant);
    void SetXName(char *str);
    void SetYName(char *str);
};

#endif /* PLOTVIEWER_H_ */
