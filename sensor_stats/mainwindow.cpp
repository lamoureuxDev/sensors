/*! \file mainwindow.cpp
 *  \author Lamoureux Développement
 *  \brief class and methods definition
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensorstat.h"
#include <common.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //! init the UI titles, height, position
    ui->temperature->set_title("Thermometer");
    ui->light->set_title("Light sensor");
    ui->humidity->set_title("Humidity sensor");
    setGeometry(500,200,width(),height());
    show();

    timer= new QTimer(this);
    timer->start(sensors.get_timeout()); //! Send a timeout signal every second
    sensors.get_shmem();  //! Get a read access to the shmem

    connect(timer,&QTimer::timeout,[this]()
    {
        /// read values from the shared memory
       float f32_hum=sensors.get_humidity();
       float f32_light=sensors.get_light();
       float f32_temp=sensors.get_temperature();

       /// set the current value of each widget sensor, which one display statistics
        ui->temperature->new_val(f32_temp);
        ui->humidity->new_val(f32_hum);
        ui->light->new_val(f32_light);
    });
}

MainWindow::~MainWindow()
{
    sensors.free_shmem();
    delete ui;
}

