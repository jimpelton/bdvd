#-------------------------------------------------
#
# Project created by QtCreator 2012-01-02T17:05:38
#
#-------------------------------------------------

QT       += core gui

TARGET = plots2
TEMPLATE = app

INCLUDEPATH += /usr/local/include/vtk-5.8/ \
               ../vv/VolumeViewer/Surface/ \
               ../vv/VolumeViewer/File/    \ 
               ../vv/VolumeViewer/Util     \
               ../vv/VolumeViewer/Viewer
               

LIBS += -L/usr/local/lib/vtk-5.8/ -L../vv/Debug/ \
        -lQVTK \
        -lQtCore \
        -lQtGui \
        -lvtksys \
        -lvtkCommon \
        -lvtkIO \
        -lvtkCharts \
        -lvv
        
QMAKE_LFLAGS += -Wl,--rpath=../vv/Debug/

SOURCES += main.cpp\
           mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
