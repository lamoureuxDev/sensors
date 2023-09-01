/*! \file main.cpp
 *  \author Lamoureux Développement
 *  \brief Main file which loads the graphic interface
 *
 *  Execute the UI which simulate sensor data, send it to a shared memory and display the current value
 */

#define VERSION "V0.0.1"

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /// \todo Use argv to run using options
    /// no graphic , version, ...

    QApplication a(argc, argv); //!< Declare to Qt that it is an application
    MainWindow w;  //!< Declare the main window
    w.show();
    return a.exec();   //!< Run the application and return when closed
}
