#include "mainwindow.h"

#include <QApplication>

string run_client();
string grafo_s;

int main(int argc, char *argv[])
{
    grafo_s = run_client();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
