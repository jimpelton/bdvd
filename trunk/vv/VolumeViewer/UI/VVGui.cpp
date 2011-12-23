/********************************************************************
	created:	16:11:2011   8:53
	filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer\VVGui.cpp
	file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\trunk\VolumeViewer
	file base:	VVGui
	file ext:	cpp
	author:		Jim Pelton
	
	purpose:	Setup the gui components.
*********************************************************************/



#include "VVGui.h"
#include "Common.h"

VVGui::VVGui(void)
{}


VVGui::~VVGui(void)
{}

QVTKWidget* VVGui::GetVtkWidget()
{
    return vtkWidget;
}



void VVGui::SetupUi(QMainWindow *MainWindow, DataReaderFormat &drf)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

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

    //--------gridLayout------//
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    gridLayout->setContentsMargins(0, 0, 0, 0);


    //-------LeftVerticalLayout--------//
    leftVerticalLayout = new QVBoxLayout();
    leftVerticalLayout->setObjectName(QString::fromUtf8("leftVerticalLayout"));
    leftVerticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

    leftColorIsoFrame = new QFrame();
    leftColorIsoFrame->setFrameStyle(QFrame::Box);
    leftColorIsoFrame->setFixedWidth(200);


    setupColorSliders();
    leftVerticalLayout->addLayout(gridLayout);
    leftColorIsoFrame->setLayout(leftVerticalLayout);
    isoSlider->setDisabled( drf.readerType == VV_POLY_DATA_READER );
    

    centralWidgetHBoxLayout->addWidget(leftColorIsoFrame);

    
    //------RightVerticalLayout--------//
    rightVerticalLayout = new QVBoxLayout();
    rightVerticalLayout->setObjectName(QString::fromUtf8("rightVerticalLayout"));
    rightVerticalLayout->setSizeConstraint(QLayout::SetNoConstraint);

    vtkWidget = new QVTKWidget();
    vtkWidget->setObjectName(QString::fromUtf8("vtkWidget"));
    QSizePolicy vtkWidgetsizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vtkWidgetsizePolicy.setHorizontalStretch(0);
    vtkWidgetsizePolicy.setVerticalStretch(0);
    //vtkWidgetsizePolicy.setHeightForWidth(vtkWidget->sizePolicy().hasHeightForWidth());
    vtkWidget->setSizePolicy(vtkWidgetsizePolicy);
    vtkWidget->setMinimumWidth(1100);

    rightVerticalLayout->addWidget(vtkWidget);

    centralWidgetHBoxLayout->addLayout(rightVerticalLayout);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, DEFAULT_WINDOW_WIDTH, 21));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);


    //QObject::connect(closeButton, SIGNAL(clicked()), vvmain, SLOT(close()));
    //QObject::connect( isoSlider,   SIGNAL( sliderPressed()  ), MainWindow, SLOT( IsoSliderClicked()) );
    QObject::connect( isoSlider,   SIGNAL( valueChanged(int)), MainWindow, SLOT( SetIsoValue(int))   );
    QObject::connect( isoSlider,   SIGNAL( sliderReleased() ), MainWindow, SLOT( RedrawRenderWindow()));

    QObject::connect( redSlider,   SIGNAL( valueChanged(int)), MainWindow, SLOT( SetRedColorValue(int)) );
    QObject::connect( redSlider,   SIGNAL( sliderReleased() ), MainWindow, SLOT( RedrawRenderWindow()) );

    QObject::connect( greenSlider, SIGNAL( valueChanged(int)), MainWindow, SLOT( SetGreenColorValue(int)) );
    QObject::connect( greenSlider, SIGNAL( sliderReleased() ), MainWindow, SLOT( RedrawRenderWindow()) );

    QObject::connect( blueSlider,  SIGNAL( valueChanged(int)), MainWindow, SLOT( SetBlueValue(int)) );
    QObject::connect( blueSlider,  SIGNAL( sliderReleased() ), MainWindow, SLOT( RedrawRenderWindow()) );

    QObject::connect( isoEdit,     SIGNAL( returnPressed() ),  MainWindow, SLOT( RedrawRenderWindow()) );

    QObject::connect( saveCurrentIsoSurfaceButton, SIGNAL( clicked() ), MainWindow, SLOT( SavePolyDataForIsoSurface()) ) ;

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi


void VVGui::setupColorSliders()
{
    
    //red stuff
    redLabel = new QLabel();
    redLabel->setObjectName(QString::fromUtf8("redLabel"));
    redLabel->setText(QString("R:"));
    gridLayout->addWidget(redLabel,0,0);

    
    redSlider = new QSlider();
    redSlider->setObjectName(QString::fromUtf8("redSlider"));
    redSlider->setOrientation(Qt::Horizontal);
    redSlider->setTickInterval(1);
    redSlider->setMinimum(0);
    redSlider->setMaximum(255);
    redSlider->setValue(DEFAULT_INITIAL_COLOR_RED);
    gridLayout->addWidget(redSlider,0,1);

    redEdit = new QLineEdit();
    redEdit->setFixedWidth(35);
    redEdit->setText(QString::number(DEFAULT_INITIAL_COLOR_RED));
    gridLayout->addWidget(redEdit,0,2);


    //green stuff
    greenLabel = new QLabel();
    greenLabel->setObjectName(QString::fromUtf8("greenLabel"));
    greenLabel->setText(QString("G:"));
    gridLayout->addWidget(greenLabel, 1, 0);

    greenSlider = new QSlider();
    greenSlider->setObjectName(QString::fromUtf8("greenSlider"));
    greenSlider->setOrientation(Qt::Horizontal);
    greenSlider->setTickInterval(1);
    greenSlider->setMinimum(0);
    greenSlider->setMaximum(255);
    greenSlider->setValue(DEFAULT_INITIAL_COLOR_GREEN);
    gridLayout->addWidget(greenSlider, 1, 1);

    greenEdit = new QLineEdit();
    greenEdit->setFixedWidth(35);
    greenEdit->setText(QString::number(DEFAULT_INITIAL_COLOR_GREEN));
    gridLayout->addWidget(greenEdit, 1, 2);


    //blue stuff
    blueLabel = new QLabel();
    blueLabel->setObjectName(QString::fromUtf8("blueLabel"));
    blueLabel->setText(QString("B:"));
    gridLayout->addWidget(blueLabel, 2, 0);

    blueSlider = new QSlider();
    blueSlider->setObjectName(QString::fromUtf8("blueSlider"));
    blueSlider->setOrientation(Qt::Horizontal);
    blueSlider->setTickInterval(1);
    blueSlider->setMinimum(0);
    blueSlider->setMaximum(255);
    blueSlider->setValue(DEFAULT_INITIAL_COLOR_BLUE);
    gridLayout->addWidget(blueSlider, 2, 1);

    blueEdit = new QLineEdit();
    blueEdit->setFixedWidth(35);
    blueEdit->setText(QString::number(DEFAULT_INITIAL_COLOR_BLUE));
    gridLayout->addWidget(blueEdit, 2,2);

    //alpha stuff
    alphaLabel = new QLabel();
    alphaLabel->setObjectName(QString::fromUtf8("alphaLabel"));
    alphaLabel->setText(QString("A:"));
    gridLayout->addWidget(alphaLabel, 3, 0);

    alphaSlider = new QSlider();
    alphaSlider->setObjectName(QString::fromUtf8("alphaSlider"));
    alphaSlider->setOrientation(Qt::Horizontal);
    alphaSlider->setMaximum(255);
    alphaSlider->setMinimum(0);
    alphaSlider->setValue(DEFAULT_INITIAL_COLOR_ALPHA);
    alphaSlider->setTickInterval(1);
    gridLayout->addWidget(alphaSlider, 3, 1);

    alphaEdit = new QLineEdit();
    alphaEdit->setFixedWidth(35);
    alphaEdit->setText(QString::number(DEFAULT_INITIAL_COLOR_ALPHA));
    gridLayout->addWidget(alphaEdit, 3,2);
    
    //iso stuff
    isoLabel = new QLabel();
    isoLabel->setObjectName(QString::fromUtf8("isoLabel"));
    isoLabel->setText(QString("ISO:"));
    gridLayout->addWidget(isoLabel, 4, 0);


    isoSlider = new QSlider();
    isoSlider->setObjectName(QString::fromUtf8("isoSlider"));
    isoSlider->setOrientation(Qt::Horizontal);
    isoSlider->setMaximum(DEFAULT_INITIAL_ISO_SLIDER_MAX);
    isoSlider->setMinimum(DEFAULT_INITIAL_ISO_SLIDER_MIN);
    isoSlider->setValue(DEFAULT_ISO_VALUE);
    isoSlider->setTickInterval(1);
    gridLayout->addWidget(isoSlider, 4, 1);

    isoEdit = new QLineEdit();
    isoEdit->setFixedWidth(35);
    isoEdit->setText(QString::number(DEFAULT_ISO_VALUE));
    gridLayout->addWidget(isoEdit, 4,2);
    
   
    saveCurrentIsoSurfaceButton = new QPushButton("Save Surface");
    saveCurrentIsoSurfaceButton->setObjectName(QString::fromUtf8("saveSurfaceButton"));
    gridLayout->addWidget(saveCurrentIsoSurfaceButton, 5,0, 1,3);

    saveScreenShotWithSurfaceCheckBox = new QCheckBox("Also Save View With Similar File Name");
    saveScreenShotWithSurfaceCheckBox->setObjectName("saveScreenShotWithSurfaceCheckBox");
    saveScreenShotWithSurfaceCheckBox->setChecked(false);
    //saveScreenShotWithSurfaceCheckBox->setText();
    gridLayout->addWidget(saveScreenShotWithSurfaceCheckBox, 6,0, 1,3);


} //setupColorSliders()
