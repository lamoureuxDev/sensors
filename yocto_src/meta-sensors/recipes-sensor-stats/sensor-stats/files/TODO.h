/*! \page TODO
  \tableofcontents
  - Ameliorations
  - Security

  \section sec Ameliorations

This program could use configuration files to manage some settings like:
 - timeout frequency
 - sensors type
 - sensors name
 - sensors value
 - sensors use range
 - number of sensors
 - shared memory path

  A Json file could be appropriate for this kind of configuration file.

  Arguments  management could be used, for some running options:
 - file loggin option : --log "/path/to/log"
 - console print enable :  --verbose
 - GUI disable option : -no-gui
 - display version : -v --version
 - display options and configuration file manual : -h --help

  \section  Security

  The shared memory path if passed via configuration file, should be secured:
 - to prevent the use of the root folder '/'
 - checking for path transversal injection (e.g /dev/shm/../../bin/sh)

 The access of data should be controled, to avoid undefined behavior.
 To do so, semaphores or mutex (sem_t) can be added to the sensor structure, stored in the shared memory.
 Before accessing to sensor data, we should use a sem_wait(),waiting for the semaphore to be released.
 Then, use a sem_post() once it is not modified.
*/
