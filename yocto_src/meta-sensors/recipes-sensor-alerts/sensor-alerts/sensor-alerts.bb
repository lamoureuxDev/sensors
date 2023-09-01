SUMMARY = "My Sensor Alert application"
LICENSE = "CLOSED"
PR = "1"

#           file://common.h \
#           file://main.cpp \
#           file://mainwindow.ui \
#           file://mainwindow.cpp \
#           file://mainwindow.h" \
#           file://sensor_alerts.pro \
#           file://sensoralert.cpp \
#           file://sensoralert.h \
#           file://sensoralert.ui"

SRC_URI = "file://common.cpp"

           

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
