
python do_display_banner() {
    bb.plain("***********************************************");
    bb.plain("*                                             *");
    bb.plain("*  Example recipe created by bitbake-layers   *");
    bb.plain("*                                             *");
    bb.plain("***********************************************");
}

addtask display_banner before do_build

SUMMARY = "My Sensor Stat application"
LICENSE = "CLOSED"
PR = "1"


#           file://common.h \
#           file://main.cpp \
#           file://mainwindow.ui \
#           file://mainwindow.cpp \
#           file://mainwindow.h" \
#           file://sensor_stats.pro \
#           file://sensorstat.cpp \
#           file://sensorstat.h \
#           file://sensorstat.ui"

SRC_URI = "file://common.cpp \
	file://main.cpp \
	file://mainwindow.ui"
           
S = "${WORKDIR}"

require recipes-qt/qt5/qt5.inc

DEPENDS += "qtbase"
inherit qmake5

#COMPILE MYIN THE DATADIR OF THE IMAGE,
do_install() {
    install -d ${D}${datadir}/${P}
    install -m 0755 ${S}/sensor-stats ${D}${datadir}/${P}
    cp -R --no-dereference --preserve=mode,links ${S} ${D}${datadir}/${P}
}

FILES_${PN} += "${datadir}"

RDEPENDS_${PN} = "qtbase qtcore"
