/*! \mainpage  README
  \tableofcontents
  - Description
  - Installation
  - Deployment
    - Linux deployment
    - Yocto deployment

  \section sec Description

The Sensor Stats program is a UI, designed to display sensors statistics values such as :
 - average
 - minimum
 - maximum

This program is intended to run at the same time as the sensor simulator. Without it, no data could be read.

A shared memory is used to communicate between processes and share sensors data.
Sensor_stat use the shared memory only for reading purpose.

Please do not run this program yourself, instead use systemd services with the attached script.



  \section Installation

    This software is based on Qt library and C++17.
    To install Qt and C++ compilator, please run the following commands on linux:
```
$ sudo apt-get install build-essential
$ sudo apt-get install qtbase5-dev
```
*
*
*   To run the program, please change your current directory to the build path.
*   Then, compile the program with qmake and make as follow:
```
$ cd /build_path
$ qmake
$ make
$ ./sensor_stats
```

  \section Deployment

  \subsection Linux

Follow these steps to deploy the sensor_stats  on your Linux system:
 - install prerequisites
 - build the app
 - move the execution file to "/usr/bin/"
 - move the sensors_script.sh file to "/usr/bin/"
 - add execution right on the script and execution file
 - create a Unit file on /lib/systemd/system/mysensors.service
 - add execution right on the Unit file
 - start the service and check that is running
 - stop it, then enable it to start on boot.

```
$ sudo apt-get install build-essential
$ sudo apt-get install qtbase5-dev
$ sudo cp sensor_stat /usr/bin
$ sudo mv sensors_script.sh /usr/bin
$ sudo chmod +x /usr/bin/sensors_script.sh
$ sudo chmod +x /usr/bin/sensor_stats
$ sudo gedit /lib/systemd/system/mysensors.service
    [Unit]
     Description= My sensors service running /usr/bin/sensors_script.sh

     [Service]
     Type=simple
     ExecStart=/bin/bash /usr/bin/sensors_script.sh

     [Install]
     WantedBy=multi-user.target

$ sudo cp /lib/systemd/system/mysensors.service /etc/systemd/system/
$ sudo chmod 644 /etc/systemd/system/mysensors.service/
$ sudo systemctl start mysensors
$ sudo systemctl stop mysensors
$ sudo systemctl enable mysensors
```

 Following theses steps, sensor_stats program will run automaticaly on boot, along side the sensor_simulator and sensor_alerts, with the sensor_simulator launched fisrt.

  \subsection Yocto

  Using yocto to build an image and add our services.

  First of all, be sure to have prerequisites for yocto:
  - A linux OS ( Docker, WSL, linux distro partition ..)
  - 100 Gb minimum free space on host disk
  - a good computer ( RAM > 16 Go, #CPU > 16) or a lot of time
  - IT network simple and reliable ( no proxy, intrusive firewall, stable connection)
  - a host updated

  Fist of all, we will need to download yocto project
```
$ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
     build-essential chrpath socat libsdl1.2-dev xterm
$ sudo apt update
$sudo apt autoremove
```

When all tools are installed, we can create our environement, creating a folder to download the Yocto Project and checkout the last version, `mickledore`

```
$ mkdir yocto
$ cd yocto
$ git clone http://git.yoctoproject.org/git/poky
$ cd poky
$ git checkout -b mickledore origin/mickledore

```

Here, we will want to build layers, and we will need bitbake tools and others. To get an easy access to them,
 we will load a special environnement from de open embedded project

```
poky$ source oe-init-build-env
### Shell environment set up for builds. ###

You can now run 'bitbake <target>'

Common targets are:
    core-image-minimal
    core-image-full-cmdline
    core-image-sato
    core-image-weston
    meta-toolchain
    meta-ide-support

Other commonly useful commands are:
 - 'devtool' and 'recipetool' handle common recipe tasks
 - 'bitbake-layers' handles common layer tasks
 - 'oe-pkgdata-util' handles common target package tasks
```

Without any option, this will create a build directory in yocto, and change our current $PWD to poky/build.
If we list directories in $poky/, we find many meta-XX folders, they are layers.
In every layer, we find one or more recipes. A recipe is a bitbake file (*.bb), wich configure the build process, commands to execute when building the recipe.

Like in the Linux deployment, we will need to install dependencies first of all, before compiling our recipe.
To know our depedencies, we have to check https://layers.openembedded.org. For meta-qt5, we can see https://github.com/meta-qt5/meta-qt5.git

to add it, we need to download it, then add the layer to our bblayer
```
poky$ git clone https://github.com/meta-qt5/meta-qt5.git
poky$ bitbake-layers add-layerr meta-qt5
poky$ bitbake-layers show-layers
layer                 path                                                                    priority
========================================================================================================

qt5-layer             /home/lamoureux/yoctoiot/layers/poky/meta-qt5                           7

```

we will try step by step to build an image with new layers, see how qt5 layers are built to build our layer

Today, I dont get yet a layer with every depedencies installed, to build my layer without any error using Qt5, but I can compiple C++ code, and have my code working but only in console, or loggin in files.
Anyway, together and with more than three days on it we will find every layers needed.

To populate our recipe for sensor-stats, we will import our source files, inherit from qtbase5 to use qmake for the compilation process

Lets build our layer, meta-sensor, and configure our recipe to build our program

```
../poky/buils$ bitbake-layers create-layer ../meta-sensors
../poky/buils$ cd ../meta-sensors
../poky/meta-sensors$ mv recipes-example recipes-sensor-stats
../poky/meta-sensors$ mv recipes-example recipes-sensor-stats

```

###############

```
root@RD-16:/home/lamoureux/yoctoiot/poky# tree meta-sensors/ -L 4
meta-sensors/
├── COPYING.MIT
├── README
├── conf
│   └── layer.conf
├── recipes-sensor-alerts
│   └── sensor-alerts
│       ├── files
│       └── sensor-alerts_0.1.bb
├── recipes-sensor-simu
│   └── sensor-simu
│       └── sensor-simu_0.1.bb
└── recipes-sensor-stats
    └── sensor-stats
        └── sensor-stats_0.1.bb
```
*/
