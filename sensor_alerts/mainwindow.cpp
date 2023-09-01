/*! \file mainwindow.cpp
 *  \author Lamoureux Développement
 *  \brief class and methods definition
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer= new QTimer(this);
    timer->start(sensors.get_timeout()); //! Send a timeout signal every second by default

    /// \todo use the internal sensor.read_conf(), to get the range value
    ///Temperature sensor alert init ( range value, title)
    ui->temperature->set_title("Temperature");
    ui->temperature->set_extrems(15,27);

    ///Humidity sensor alert init ( range value, title)
    ui->humidity->set_title("Humidity");
    ui->humidity->set_extrems(30,80);

    ///light sensor alert init ( range value, title)
    ui->light->set_title("Light");
    ui->light->set_extrems(10,90);

    sensors.get_shmem();

    connect(timer,&QTimer::timeout,[this]()
    {
        /// \todo Use the sensors settings to know how many sensors are available
        /// and use an array of sensors with get_value() methode to be momre generic

        /// read sensor data from the shared memory
        float f32_hum=sensors.get_humidity();
        float f32_light=sensors.get_light();
        float f32_temp=sensors.get_temperature();

        ///Send sensors data to each SensorAlert object, to display alerts, regarding normal range value
        ui->light->set_val( f32_light);
        ui->humidity->set_val(f32_hum);
        ui->temperature->set_val(f32_temp);
    });
    setGeometry(100,200,width(),height());
    show();

}

MainWindow::~MainWindow()
{
    sensors.free_shmem(); // detach from the shared memory when killed
    delete ui;
}

