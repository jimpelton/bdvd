/*
 * PlotViewerMain.h
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 */

#ifndef PLOTVIEWERMAIN_H_
#define PLOTVIEWERMAIN_H_

#include "DataReaderFormat.h"
#include "ViewerOptions.h"
#include "PlotViewer.h"
#include "PlotViewerGui.h"
#include "ViewerOptions.h"


#include <QtGui/QMainWindow>
#include <QtCore/QObject>

class PlotViewerMain : public QMainWindow, public Ui::PVGUI{

private:
	Q_OBJECT


	PlotViewer *m_plotViewer;
	DataReaderFormat m_drf;
	ViewerOptions m_vopt;



public:
	PlotViewerMain(DataReaderFormat drf, ViewerOptions vopt);
	virtual ~PlotViewerMain();

	int Setup();
	void InitializeRenderer();

	void TriangleEdgeLength();


};

#endif /* PLOTVIEWERMAIN_H_ */
