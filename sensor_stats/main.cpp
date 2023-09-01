/*! \file main.cpp
 *  \author Lamoureux Développement
 *  \brief Main file which loads the graphic interface
 */



#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //!< Declare to Qt that it is an application
    MainWindow w;  //!< Declare the main window
    w.show();
    return a.exec();   //!< Run the application and return when closed
}
