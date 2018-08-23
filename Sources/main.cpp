#include "mainwindow.h"
#include <QApplication>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;



int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
