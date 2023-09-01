/*! \file common.h
 *  \author Lamoureux Développement
    \brief Declaration of st_sensors structure and common class
*/

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdlib>
#include <unistd.h>
#include <semaphore.h>

/// \todo add a st_sensor_data
/// with normal range value, current value and use it in st_sensors


/*! \struct st_sensors
    \brief A st_sensors structure

    Data sensors value
*/
struct st_sensors
{
    float f32_temperature; /*!< a float temperature value */
    float f32_humidity;    /*!< a float humidity value */
    float f32_light;       /*!< a float light value */
};


/*! \class Common
    \brief A Common class to access the sensor shared memory

    getters et setters to sensors value. Create, get and free access to the shared memory
*/
class  Common
{
    int shmId;  //!< Brief Private share memory ID : shmId
    st_sensors *sensors; //!< Brief private pointer to a structure st_sensors
    unsigned int u32_timeout{1000}; //!< Brief waiting time in millisecond before accessing the shmem, 1 second by default

    /**
    * \fn void read_conf()
    * \brief read a conf file to set the shmem settings
    *
    * Settings: Number of sensors, timeout access, shmem to access
    */
    void read_conf(void);
public:

    /**
    * Common constructor.
    */
    Common(void);

    /**
    * Common destructor
    * free the access to the shared memory
    */
    ~Common();


    /**
    * \fn get_timeout()
    * get the timemout value in milliseconds
    *
    * \return the timeout value by default, or read in the conf file
    */
    unsigned int get_timeout(void) const {return u32_timeout;};


    /**
    * \fn free_shmem()
    * free the access to the shared memory
    *
    * sensors is detached from the shared memory
    */
    void free_shmem(void);

    /**
    *\fn void create_shmem()
    * create the access to the shared memory
    * Attach sensors to the shared memory
    */
    void create_shmem(void);

    /**
    * \fn void get_shmem()
    * get the access to the shared memory
    * Attach sensors to the shared memory
    */
    void get_shmem(void);

    /**
    * \fn void set_light(float f32_val)
    * setter to the light value in the shared memory
    * \param f32_val light value
    */
    void set_light(float f32_val);

    /**
    * \fn void set_humidity(float f32_val)
    * setter to the humidity value in the shared memory
    * \param f32_val humidity value
    */
    void set_humidity(float f32_val);

    /**
    * \fn void set_temperature(float f32_val)
    * setter to the temperature value in the shared memory
    * \param f32_val temperature value
    */
    void set_temperature(float f32_val);

    /**
    * \fn float get_light(void) const
    * getter to the light value in the shared memory
    * \return float light value
    */
    float get_light() const;

    /**
    * \fn float get_temperature(void) const
    * getter to the temperature value in the shared memory
    * \return float temperature value
    */
    float get_temperature() const;

    /**
    * \fn float get_humidity(void) const
    * getter to the humidity value in the shared memory
    * \return float humidity value
    */
    float get_humidity() const;
};

#endif // COMMON_H
