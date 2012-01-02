/********************************************************************
 created:	2011/10/18
 created:	18:10:2011   11:08
 filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer\VVGui.h
 file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer
 file base:	VVGui
 file ext:	h
 author:		Jim Pelton

 purpose:	Contains the implementation of the GUI.
            Contains the QVTKWidget!
*********************************************************************/



#ifndef VVGUI_H_
#define VVGUI_H_

#include "ViewerOptions.h"

#include <QVTKWidget.h>
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



class VVGui
{
private:

    void setupColorSliders();

public:

    QWidget *centralwidget;

    QGridLayout *gridLayout;
    QHBoxLayout *centralWidgetHBoxLayout;
    QVBoxLayout *rightVerticalLayout;
    QVBoxLayout *leftVerticalLayout;
    QFormLayout *colorAndIsoSliderFormLayout;

    QFrame *leftColorIsoFrame;

    QLabel *redLabel,
           *greenLabel,
           *blueLabel,
           *isoLabel,
           *alphaLabel;

    QSlider *redSlider,
            *greenSlider,
            *blueSlider,
            *alphaSlider,
            *isoSlider;

    QLineEdit *redEdit,
              *greenEdit,
              *blueEdit,
              *isoEdit,
              *alphaEdit;

    QPushButton *saveCurrentIsoSurfaceButton;
    QPushButton *saveScreenShotButton;

    QCheckBox  *saveScreenShotWithSurfaceCheckBox;

    QSpacerItem *verticalSpacer;
    QVTKWidget  *vtkWidget;
    QMenuBar    *menubar;
    QStatusBar  *statusbar;
    


public:
    VVGui(void);
    ~VVGui(void);

    QVTKWidget* GetVtkWidget();

    void SetupUi(QMainWindow *GUI, ViewerOptions&);
    

};

namespace Ui {
class GUI: public VVGui {};
} // namespace Ui

#endif
