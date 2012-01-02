/*
 * PlotViewerGui.h
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 */

#ifndef PLOTVIEWERGUI_H_
#define PLOTVIEWERGUI_H_

#include "DataReaderFormat.h"

#include <QVTKWidget.h>
#include <vtkQtTableView.h>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>

#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QVBoxLayout>

#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>

#include <QtGui/QFrame>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>


class PlotViewerGui {
public:

	QWidget *centralwidget;
	QHBoxLayout *centralWidgetHBoxLayout;

	QVTKWidget *plotVtkWidget;
	//vtkQtTableView *tableVtkWidget;



	PlotViewerGui();
	virtual ~PlotViewerGui();

	void SetupUi(QMainWindow *GUI, DataReaderFormat&);
};

namespace Ui {
	class PVGUI: public PlotViewerGui {};
} // namespace Ui

#endif /* PLOTVIEWERGUI_H_ */
