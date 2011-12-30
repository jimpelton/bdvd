/*
 * PlotViewerGui.cpp
 *
 *  Created on: Dec 27, 2011
 *      Author: jim
 */

#include "PlotViewerGui.h"

PlotViewerGui::PlotViewerGui() {


}

PlotViewerGui::~PlotViewerGui() {

}



void PlotViewerGui::SetupUi(QMainWindow *MainWindow, DataReaderFormat &drf)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(1150, 600);
    //MainWindow->setGeometry(0,0,1150,600);

    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
    centralwidget->setSizePolicy(sizePolicy);

    centralWidgetHBoxLayout = new QHBoxLayout(centralwidget);
    centralWidgetHBoxLayout->setObjectName(QString::fromUtf8("centralWidgetHBoxLayout"));
    centralWidgetHBoxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

    plotVtkWidget = new QVTKWidget();
    plotVtkWidget->setObjectName(QString::fromUtf8("plotVtkWidget"));
    QSizePolicy plotVtkWidgetSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plotVtkWidgetSizePolicy.setHorizontalStretch(0);
    plotVtkWidgetSizePolicy.setVerticalStretch(0);
    plotVtkWidget->setSizePolicy(plotVtkWidgetSizePolicy);
    plotVtkWidget->setMinimumWidth(300);

    centralWidgetHBoxLayout->addWidget(plotVtkWidget);



    //tableVtkWidget = new vtkQtTableView();
    //tableVtkWidget->setObjectName(QString::fromUtf8("tableVtkWidget"));
    //QSizePolicy tableVtkWidgetSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //tableVtkWidgetSizePolicy.setHorizontalStretch(0);
    //tableVtkWidgetSizePolicy.setVerticalStretch(0);
    //tableVtkWidget->setSizePolicy(tableVtkWidgetSizePolicy);
    //tableVtkWidget->setMinimumWidth(300);

    //centralWidgetHBoxLayout->addWidget(tableVtkWidget);


    MainWindow->setCentralWidget(centralwidget);
//    menubar = new QMenuBar(MainWindow);
//    menubar->setObjectName(QString::fromUtf8("menubar"));
//    menubar->setGeometry(QRect(0, 0, DEFAULT_WINDOW_WIDTH, 21));
//    MainWindow->setMenuBar(menubar);
//    statusbar = new QStatusBar(MainWindow);
//    statusbar->setObjectName(QString::fromUtf8("statusbar"));
//    MainWindow->setStatusBar(statusbar);



}
