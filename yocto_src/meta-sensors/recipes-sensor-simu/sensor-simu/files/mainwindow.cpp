/*! \file mainwindow.cpp
 *  \author Lamoureux Développement
 *  \brief class and methods definition
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    setGeometry(300,200,width(),height());
    show();
    sensors.create_shmem();  //! Create and get an access to the shmem


    connect(timer,&QTimer::timeout,[this]()
    {
        /// \todo Use the sensors settings to know how many sensors are available
        /// and to set the range value too
        float f32_hum = (rand()%100); //! Define a random humidity value in [0.0 - 100]
        float f32_light= (rand()%100);//! Define a random light value in [0.0 - 100]
        float f32_temp= (-10 + (rand()%50)); //! Define a random temperature value in [-10 - 40]


        //! Write random values to the shared memory
        sensors.set_humidity(f32_hum);
        sensors.set_light(f32_light);
        sensors.set_temperature(f32_temp);

        //! Display the sensors values
        set_temp(f32_temp);
        set_humidity(f32_hum);
        set_light(f32_light);

    });

}

MainWindow::~MainWindow()
{
    sensors.free_shmem();
    delete ui;
}

void MainWindow::set_temp(float f32_temp)
{
    ui->spin_temp->setValue(f32_temp);
}

void MainWindow::set_humidity(float f32_hum)
{
    ui->spin_humidity->setValue(f32_hum);
}

void MainWindow::set_light(float f32_light)
{
    ui->spin_light->setValue(f32_light);
}

