/*! \file sensorstat.cpp
 *  \author Lamoureux Développement
 *  \brief class and methods definition
*/
#include "sensorstat.h"
#include "ui_sensorstat.h"
#include <QString>

SensorStat::SensorStat(QWidget *parent, std::string name) :
    QWidget(parent),
    ui(new Ui::SensorStat)
{
    ui->setupUi(this);
    ui->title->setText("toto");
}


SensorStat::~SensorStat()
{
    delete ui;
}

void SensorStat::new_val(float f32_val)
{
    f32_sum = f32_val + f32_sum;
    u32_cpt++;
    set_min( f32_val);
    set_max(f32_val);
    set_avg();
    display_stats();
}

void SensorStat::set_title(std::string name)
{
    str_name=name;

    ui->title->setText(str_name.c_str());

}

void SensorStat::display_stats()
{
    ui->spin_min->setValue(f32_min);
    ui->spin_max->setValue(f32_max);
    ui->spin_avg->setValue(f32_avg);
}

void SensorStat::set_avg(void)
{
    assert(u32_cpt >0 );
    f32_avg = (f32_sum / u32_cpt);

}

void SensorStat::set_max(float f32_val)
{
    if(f32_val > f32_max)
    {
        f32_max= f32_val;
    }
}
void SensorStat::set_min(float f32_val)
{
    if(f32_val < f32_min)
    {
        f32_min= f32_val;
    }
}
