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

#include <vtkTextWidget.h>

#include <vector>

struct plot{
	int type;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	char *label;
};

class PlotViewer : Viewer {

private:

	std::vector<vtkSmartPointer<vtkDataArray> > m_yArrays;

//	const unsigned char NUM_COMPONENTS_SET = 0x01;
//	const unsigned char ROW_VALUE_SET = 0x02;
//	const unsigned char X_ARRAY_SET = 0x04;
//	const unsigned char Y_ARRAY_SET = 0x08;
//	unsigned char allComponentsSet;

	vtkSmartPointer<vtkContextView> view;
	vtkSmartPointer<vtkTable> table;

	vtkSmartPointer<vtkChartXY> chart;
	vtkSmartPointer<vtkAlgorithm> reader;

	vtkSmartPointer<vtkDataArray> m_arrX;

	std::vector<plot> m_plots;

	int m_numComponents;


public:
	PlotViewer(DataReaderFormat drf, int screenWidth, int screenHeight);
	~PlotViewer();

	///////overrides from Viewer///////
	int Setup();
	void InitializeRenderer();
	void Refresh();


    vtkSmartPointer<vtkContextView> GetView() const;
    vtkSmartPointer<vtkTable> GetTable() const;

    void SetXArray(vtkSmartPointer<vtkDataArray> arrX, char *arrName);
    void AddYArray(vtkSmartPointer<vtkDataArray> arrY, char *arrName, plot *p);
    void SetNumComponents(int n);
    void SetRowValue(vtkIdType, vtkIdType, vtkVariant);
    void SetXName(char *str);

};

#endif /* PLOTVIEWER_H_ */
