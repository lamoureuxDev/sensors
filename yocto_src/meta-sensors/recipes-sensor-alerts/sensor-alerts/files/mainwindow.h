/*! \file mainwindow.h
 *  \author Lamoureux Développement
    \brief Declaration of Mainwindow class

    Access to a shared memory, read sensors data from it and display statistics
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
    \brief A MainWindow class to statistics sensors data

    Display temperature, humidity and light statistics value

*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Common sensors; /**< sensors : should be in a lib, set of Setters/Getters to the shared memory */
    QTimer *timer; /**< timer to access every second to the shared memory */

public:
    /*!
     * \brief MainWindow - define a window with 3 sensors alerts.
     * Updated values every second by default , if the current value read from the shared memory
     * is out of normal range value, an alert is displayed in the UI.
     * \param parent
     */
    MainWindow(QWidget *parent = nullptr);

    /**
    * MainWindow destructor
    * destroy the ui member
    */
    ~MainWindow();


private:
    Ui::MainWindow *ui; /**< Graphic user interface */
};
#endif // MAINWINDOW_H
