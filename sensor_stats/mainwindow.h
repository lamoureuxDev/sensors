/*! \file common.h
 *  \author Lamoureux Développement
 *  \brief Declaration of Sensor Stat main window
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <common.h>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*! \class MainWindow
    \brief A MainWindow class to display sensors statistics

    Display temperature, humidity and light statistics values
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT   /*!< Macro to manage signals and slots */

    Common sensors; //!< Brief private member which read sensors data
    QTimer *timer;  //!< Brief private timer to read every second sensors data

public:
    /**
    * MainWindow constructor.
    *
    * set the ui, timer and a lambda slot to display sensors stats every second
    */
    MainWindow(QWidget *parent = nullptr);

    /**
    * MainWindow destructor
    * destroy the ui member
    */
    ~MainWindow();

private:
    Ui::MainWindow *ui;  //!< Brief private member to the graphic view which contains 3 <class>SensorStat</class>
};
#endif // MAINWINDOW_H
