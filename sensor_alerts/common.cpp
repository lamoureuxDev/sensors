/*! \file common.cpp
    \brief class and methods definition
*/
#include "common.h"
#include <stdlib.h>     /* srand, rand */
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

//#define SHMEM_SENSORS "/dev/shm/simulated_sensors"
#define SHMEM_SENSORS "/home/lamoureux/yoctoiot/Services/sensor_simulator/simulated_sensors"


void Common::read_conf()
{
/// \todo Read a conf file
/// if file.exists()
/// {
///    [timeout]
///    ->   u32_timeout = val();
///    [shmem_paths]
///    ->  /dev/shmem/sensors/temperature
///    ->  /dev/shmem/sensors/light
/// }
}

Common::Common(void)
{

}

Common::~Common()
{
    free_shmem();
}

void Common::free_shmem()
{
    shmdt(sensors);

}
/*!
 * \brief Common::create_shmem()
 *
 * Get a key to the shmem path
 * Get the shmId the shared memory and create the shared memory if does not exists
 * Attach the sensors member to the shmem
 */
void Common::create_shmem()
{
    key_t key = ftok(SHMEM_SENSORS, 'W');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    shmId = shmget(key, sizeof(st_sensors), 0666 | IPC_CREAT);
    if (shmId == -1) {
        perror("shmget");
        exit(1);
    }
    sensors = (st_sensors*)shmat(shmId, nullptr, 0);
       if (sensors == (st_sensors*)-1) {
           perror("shmat");
           exit(1);
       }
}

/*!
 * \brief Common::get_shmem()
 *
 * Get a key to the shmem path
 * Get the shmId the shared memory
 * Attach the sensors member to the shmem
 */
void Common::get_shmem()
{
    key_t key = ftok(SHMEM_SENSORS, 'W');
       if (key == -1) {
           perror("ftok");
           exit(1);
       }

       shmId = shmget(key, sizeof(st_sensors), 0666);
       if (shmId == -1) {
           perror("shmget");
           exit(1);
       }

      sensors = (st_sensors*)shmat(shmId, nullptr, 0);
         if (sensors == (st_sensors*)-1) {
             perror("shmat");
             exit(1);
         }
}


void Common::set_light(float f32_val)
{
    sensors->f32_light=f32_val;
}

void Common::set_humidity(float f32_val)
{
    sensors->f32_humidity=f32_val;
}

void Common::set_temperature(float f32_val)
{
    sensors->f32_temperature=f32_val;
}

float Common::get_light() const
{
    float f32_ret;
    f32_ret = sensors->f32_light;
    return f32_ret;
}
float Common::get_humidity() const
{
    float f32_ret;
    f32_ret = sensors->f32_humidity;
    return f32_ret;
}
float Common::get_temperature() const
{
    float f32_ret;
    f32_ret = sensors->f32_temperature;
    return f32_ret;
}


