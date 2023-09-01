/*! \file mainwindow.h
 *  \author Lamoureux Développement
    \brief Declaration of Mainwindow class

    Create a shared memory and send sensors data to it
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
    \brief A MainWindow class to simulate sensors data

    Set temperature, humidity and light value in a shared memory

*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Common sensors;//!< Brief private member used to write sensors data
    QTimer *timer;  //!< Brief private timer to simulate every second sensors data

public:
    /**
    *\brief Set the ui, timer and a lambda slot to display sensors stats every second
    *Everytime the timer::timeout signal is emitted, a random value is setted in the
    * shared memoryand displayed the UI.
    *\param parent
    */
    MainWindow(QWidget *parent = nullptr);


    /**
    * MainWindow destructor
    * destroy the ui member
    */
    ~MainWindow();

    /**
    * \fn set_temp(float f32_temp)
    * \brief set the temperature value in the UI
    *
    * \param f32_temp current sensor value
    */
    void set_temp(float f32_temp);

    /**
    * \fn set_humidityset_humidity(float f32_hum)
    * \brief set the humidity  value in the UI
    *
    * \param f32_hum current sensor value
    */
    void set_humidity(float f32_hum);

    /**
    * \fn set_light(float f32_light)
    * \brief set the light  value in the UI
    *
    * \param f32_light current sensor value
    */
    void set_light(float f32_light);

private:
    Ui::MainWindow *ui;   //!< Brief Ui class to display sensor values
};
#endif // MAINWINDOW_H
