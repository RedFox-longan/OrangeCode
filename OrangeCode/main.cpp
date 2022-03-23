#include "mainwindow.h"
#include "oc_start.h"

#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    OC_Start start;
    MainWindow window;
    window.setWindowTitle("Orange Code v0.0.1-alpha");
    window.resize(800, 600);

    start.exec();
    window.show();
    return app.exec();
}
