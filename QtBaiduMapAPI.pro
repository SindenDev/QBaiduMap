#-------------------------------------------------
#
# Project created by QtCreator 2015-06-29T16:42:32
#
#-------------------------------------------------

QT += core gui positioning webkitwidgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtBaiduMapAPI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logfilepositionsource.cpp

HEADERS  += mainwindow.h \
    logfilepositionsource.h

FORMS    += mainwindow.ui

RESOURCES += \
    htmlfile.qrc
