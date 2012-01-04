
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

    vector<QString*> *d = new vector<QString*>(4);
    d->push_back(new QString(argv[1]));
    d->push_back(new QString(argv[2]));
    d->push_back(new QString(argv[3]));
    d->push_back(new QString(argv[4]));

    vector<string> *ltext = new vector<string>(4);
    ltext->push_back(argv[5]);
    ltext->push_back(argv[6]);
    ltext->push_back(argv[7]);
    ltext->push_back(argv[8]);


    MainWindow w(d, ltext);
    w.show();

    return a.exec();
}
