#ifndef SENSORALERT_H
#define SENSORALERT_H

#include <QFrame>

namespace Ui {
class SensorAlert;
}

class SensorAlert : public QFrame
{
    Q_OBJECT

    float min{10000},max{-10000};
    QString alerte_msg;
public:
    explicit SensorAlert(QWidget *parent = nullptr);
    ~SensorAlert();
    void set_extrems(float f32_min,float f32_max);
    bool  is_extrem(float f32_val);
    void set_val(float f32_val);
    void set_title(std::string name);

private:
    Ui::SensorAlert *ui;
};

#endif // SENSORALERT_H
