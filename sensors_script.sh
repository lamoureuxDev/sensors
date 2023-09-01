#!/bin/bash
# Author : Lamoureux Developpement 2023
#Description: 
# Bash script launched as daemon when the OS start up.
# place this script in the same folder of the 3 other programs
#
#This script run a sensor simulator, sensor_stat and sensor_alert program
# this set of programs, exchange data via a shared memory

#AUTO KILL after 2 minutes

#create the shmem before just in case ..
#TODO use the shared memory /dev/shmem/simulated_sensors on production environment
# And the creationn part will not be necessary in production environment
mkdir /home/lamoureux
mkdir /home/lamoureux/yoctoiot
mkdir /home/lamoureux/yoctoiot/Services
mkdir /home/lamoureux/yoctoiot/Services/sensor_similator
echo "">> /home/lamoureux/yoctoiot/Services/sensor_simulator/simulated_sensors
# end of shmem creation

rm log
./sensor_simulator >> log &
./sensor_stats >> log &
./sensor_alerts >> log &

sleep 120

killall sensor_*