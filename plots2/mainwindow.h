#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vtkSmartPointer.h>
#include <vtkContextView.h>
#include <vtkTable.h>
#include <vtkChartXY.h>
#include <vtkAlgorithm.h>
#include <vtkPolyData.h>


#include <QMainWindow>
#include <QFileInfoList>
#include <QString>

#include <vector>
#include <string>

using std::string;
using std::vector;

#define VTKCREATE(type, name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(vector<QString*>*, vector<string>*, QWidget *parent = 0 );
    //explicit MainWindow( QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setup();
    QFileInfoList fileNames(QString *d);
    double SurfaceArea(vtkPolyData *);
    void textstuff(vtkContextView*);
    void legendstuff(vtkContextView *cv);
};

#endif // MAINWINDOW_H
