
#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QString>


#include <vector>
#include <string>

using std::vector;
using std::string;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QStrings because these will be used for a QDir
    vector<QString*> *d = new vector<QString*>();
    d->push_back(new QString(argv[1]));
    d->push_back(new QString(argv[2]));
    d->push_back(new QString(argv[3]));
    d->push_back(new QString(argv[4]));

    //regular strings because these will be used with vtk.
    vector<string> *ltext = new vector<string>();
    ltext->push_back(argv[5]);
    ltext->push_back(argv[6]);
    ltext->push_back(argv[7]);
    ltext->push_back(argv[8]);


    MainWindow w(d, ltext);
    w.show();
    int rval = a.exec();

//    for (std::vector<QString*>::iterator it = d->begin();
//    		it < d->end(); ++it)
//    {
//    	delete *it;
//    }
//    delete d;
//    delete ltext;

    return rval;
}
