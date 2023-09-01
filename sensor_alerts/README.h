/*! \mainpage  README
  \tableofcontents
  - Description
  - Installation
  - Deployment
    - Linux deployment
    - Yocto deployment

  \section sec Description

The Sensor Alerts program is a UI, designed to display a sensors alert message when the current value is out of normal range value.
The normal range value is setting in the init process, then compare the current value with the range.

The UI contains the current date and the last alert message with the date.

By default, the alert message windows update values every second.

This program is intended to run at the same time as the sensor simulator. Without it, no data could be read.

A shared memory is used to communicate between processes and share sensors data.
Sensor_alerts use the shared memory only for reading purpose.

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
$ ./sensor_alerts
```

  \section Deployment

  \subsection Linux

Follow these steps to deploy the Sensor_alerts  on your Linux system:
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
$ sudo cp Sensor_alerts /usr/bin
$ sudo mv sensors_script.sh /usr/bin
$ sudo chmod +x /usr/bin/sensors_script.sh
$ sudo chmod +x /usr/bin/sensor_alerts
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

 Following theses steps, Sensor_alerts program will run automaticaly on boot, along side the sensor_simulator and Sensor_stats, with the sensor_simulator launched fisrt.

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

Today, I dont get yet a layer with every depedencies installed, to build my layer without any error using Qt5, but I can compile C++ code, and have my code working but only in console, or loggin in files.
Anyway, together and with more than three days on it we will find every layers needed. In order to run my qt application, we could use a pre cross compilation for the target, then copy the binary file in ${bindir}

To populate our recipe for sensor-alerts, we will import our source files in our recipe to get this architecture:
(assuming that $BUILD_Sensor_ALERTS= /path/to/Sensor_alerts_sources)

```
../poky/buils$ bitbake-layers create-layer ../meta-sensors
../poky/buils$ cd ../meta-sensors
../poky/meta-sensors$ mv recipes-example recipes-sensor-alerts
../poky/meta-sensors$ mkdir recipes-sensor-alerts/sensor-alerts
../poky/meta-sensors$ mkdir recipes-sensor-alerts/sensor-alerts/files
../poky/meta-sensors$ cp $BUILD_Sensor_ALERTS/*.* recipes-sensor-alerts/sensor-alerts/files/
...poky/meta-sensors$ tree recipes-sensor-alerts/ -L 3
recipes-sensor-alerts/
└── sensor-alerts
    ├── files
    │   ├── README.h
    │   ├── TODO.h
    │   ├── common.cpp
    │   ├── common.h
    │   ├── main.cpp
    │   ├── mainwindow.cpp
    │   ├── mainwindow.h
    │   ├── mainwindow.ui
    │   ├── Sensor_alerts.pro
    │   ├── Sensor_alerts.pro.user
    │   ├── sensorstat.cpp
    │   ├── sensorstat.h
    │   └── sensorstat.ui
    └── sensor-stats_0.1.bb

2 directories, 14 files

../poky/buils$ bitbake-layers add-layer ../meta-sensors

```

We will edit our recipe sensor-alerts_0.1.bb as follow :

```
SUMMARY = "My Sensor Alert application"
LICENSE = "CLOSED"
PR = "1"

SRC_URI = "file://common.cpp \
           file://common.h \
           file://main.cpp \
           file://mainwindow.ui \
           file://mainwindow.cpp \
           file://mainwindow.h \
           file://sensor_alerts.pro \
           file://sensoralert.cpp \
           file://sensoralert.h \
           file://sensoralert.ui "
           

S = "${WORKDIR}"

require recipes-qt/qt5/qt5.inc

DEPENDS += "qtbase"
inherit qmake5

#COMPILE MYIN THE DATADIR OF THE IMAGE,
do_install() {
    install -d ${D}${datadir}/${P}
    install -m 0755 ${S}/sensor-alerts ${D}${datadir}/${P}
    cp -R --no-dereference --preserve=mode,links ${S} ${D}${datadir}/${P}
}

FILES_${PN} += "${datadir}"

RDEPENDS_${PN} = "qtbase qtcore"
```

For the other recipes, we will follow the same process, to obtain the following architecture

```
...poky$ tree meta-sensors/ -L 4
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

In our build local.conf, we will need to add some options in order to build images.
But still trying to find the correct conf honestly, for now I have add this settings 
and have Qt5everywheredemo running, but using cmake to compile and using QML instead of ui.

```
##services systemd

DISTRO_FEATURES:append = " systemd"
DISTRO_FEATURES:BACKFILL_CONSIDERED += "sysvinit"
VIRTUAL-RUNTIME:init_manager = "systemd"
VIRTUAL-RUNTIME:initscripts = "systemd-compat-units"

##Default distro
DISTRO ?= "poky"

## Trying to compile on host if possible 
IMAGE_FEATURES += " tools-sdk tools-debug eclipse-debug dev-pkgs "
EXTRA_IMAGE_FEATURES ?= "debug-tweaks tools-sdk dev-pkgs"

## Adding Qt lib, projects, and qt5everywhere runs on target, but it uses QML, not ui
IMAGE_INSTALL:append = " nano qtbase qtbase-tools qtdeclarative qt5everywheredemo"
DISTRO_FEATURES:append = " qt5"
PACKAGECONFIG:append_pn-qtbase = " icu"
PACKAGECONFIG:append:pn-qemu-system-native = " gtk+"
```



*/

