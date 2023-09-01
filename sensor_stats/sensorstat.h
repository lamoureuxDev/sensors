/*! \file sensostat.h
 *  \author Lamoureux Développement
 *  \brief Declaration of Sensor class
 *
 *  A graphic box with sensor value statistics and a set of statistics functions for sensor values
*/

#ifndef SENSORSTAT_H
#define SENSORSTAT_H

#include <QWidget>


namespace Ui {
class SensorStat;
}

/*! \class SensorStat
    \brief A SensorStat class to compute and display a sensor statistic
*/
class SensorStat : public QWidget
{
    Q_OBJECT  /*!< Macro to manage signals and slots */

    uint32_t u32_cpt{0}; //!< Brief private counter value for average value
    float f32_sum{0}; //!< Brief private sum value  for average value
    float f32_min{10000}; //!< Brief private minimum value
    float f32_max{-1000}; //!< Brief private maximum value
    float f32_avg{0}; //!< Brief private average value

    /**
    * \fn set_avg()
    * set the f32_avg value from f32_sum and u32_cpt
    */
    void set_avg(void);

    /**
    * \fn set_max()
    * set the f32_max value from the current sensor value and f32_max value
    * \param f32_val current sensor value
    */
    void set_max(float f32_val);

    /**
    * \fn set_min()
    * set the f32_min value from the current sensor value and f32_min value
    * \param f32_val current sensor value
    */
    void set_min(float f32_val);

    std::string str_name;   //!< Brief private sensor name

    /**
    * \fn display_stats()
    * Display all the sensor statistics
    */
    void display_stats();

public:

    /**
    * SensorStat constructor
    * \param parent : object parent
    * \param name : sensor name
    */
    explicit SensorStat(QWidget *parent = nullptr, std::string name="Sensor");

    /**
    * SensorStat destructor
    * destroy the ui
    */
    ~SensorStat();

    /**
    * \fn void new_val(float f32_val)
    * \brief set the current sensor value
    *
    * All statistics are computed in this method
    *
    * \param float f32_val : current value
    */
    void new_val(float f32_val);

    /**
    * \fn  float get_avg()const
    * get the average sensor value
    *
    * \return f32_avg the sensor average value
    */
    float get_avg()const {return f32_avg;};

    /**
    * \fn  float get_max()const
    * get the maximum sensor value
    *
    * \return f32_max the sensor average value
    */
    float get_max()const {return f32_max;};

    /**
    * \fn  float get_min()const
    * get the minimum sensor value
    *
    * \return f32_min the sensor average value
    */
    float get_min()const {return f32_min;};

    /**
    * \fn  void set_title(std::string name)
    * set the title of the widget
     */
    void set_title(std::string name);

private:
    Ui::SensorStat *ui;
};

#endif // SENSORSTAT_H
