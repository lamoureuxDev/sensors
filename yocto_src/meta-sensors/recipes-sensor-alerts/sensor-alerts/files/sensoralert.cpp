#include "sensoralert.h"
#include "ui_sensoralert.h"
#include <QDateTime>
SensorAlert::SensorAlert(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SensorAlert)
{
    ui->setupUi(this);
    alerte_msg="";
}

SensorAlert::~SensorAlert()
{
    delete ui;
}

void SensorAlert::set_extrems(float f32_min, float f32_max)
{
    min=f32_min;
    max=f32_max;
}

bool SensorAlert::is_extrem(float f32_val)
{
    QString date= (QString("current date : ")+QDateTime::currentDateTime().toString("MM/dd/yyyy - hh:mm:ss") );

    bool ret{false};
    if((f32_val<min )|| (f32_val >max))
    {

       alerte_msg=(QString("<br><br><b>Alert</b>: sensor value was "+QString::number(f32_val,'g',2))+ QString(" when normal range is [") + QString::number(min,'g',2) + QString(" - ") +  QString::number(max,'g',2) + QString(" ] at ")+QDateTime::currentDateTime().toString("MM/dd/yyyy - hh:mm:ss")  );
        ret=true;
    }
    ui->alerte->setHtml(date+alerte_msg);

    return ret;
}

void SensorAlert::set_val(float f32_val)
{
    is_extrem(f32_val);
}

void SensorAlert::set_title(std::string name)
{
    ui->title->setText(name.c_str());
}
