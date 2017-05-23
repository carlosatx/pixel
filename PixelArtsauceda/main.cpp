#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);     //The QApplication class manages the GUI application's control flow and main settings.
    MainWindow window;       // declare the object of MainWindow for Display the Application
    window.show();           // from the declare object,call the show function to display

    return app.exec();   //--- a.exec() does not return untill the application is quit,
}
