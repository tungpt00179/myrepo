#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T17:49:33
#
#-------------------------------------------------

QT       += core gui network sql

# wget -c -t 0 --timeout=60 --waitretry=60 URL_of_file

# The application version
VERSION = 1.0.0

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Define the preprocessor macro to get the application version in our application.
DEFINES += BRAND_NAME=\\\"BusXanh\\\"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

#TARGET = CheapTaxiGui_$$VERSION
TARGET = DiemTram.bin
TEMPLATE = app
CONFIG   -= app_bundle
unix:!macx:{
CONFIG += serialport
}

#INCLUDEPATH += $$OUT_PWD

SOURCES += \
    CheapDB/cheapdb.cpp \
    Gui/driverform.cpp \
    Gui/main.cpp \
    models/command/command.cpp \
    models/command/commandfactory.cpp \
    models/profiles/driverprofile.cpp \
    models/response/responseparser.cpp \
    network/core_network.cpp \
    utils/config/deviceconfig.cpp



unix:SOURCES +=

HEADERS  += \
    CheapDB/cheapdb.h \
    Gui/driverform.h \
    models/command/command.h \
    models/command/commandfactory.h \
    models/profiles/driverprofile.h \
    models/response/response.h \
    models/response/responseparser.h \
    models/common.h \
    network/core_network.h \
    #network/core_network_task.h \
    utils/config/deviceconfig.h \
    utils/log/log.h \
    models/models.h

unix: HEADERS +=

FORMS += \
    Gui/driverform.ui


unix: INCLUDEPATH += /usr/local/include/
unix: LIBS += -L /usr/local/lib/ -lqjson

unix:!macx: LIBS += -lX11 -lwiringPi

macx: LIBS += -L/opt/local/lib/ -lgps

INCLUDEPATH += /opt/local/include
DEPENDPATH += /opt/local/include

DISTFILES += \
    config/settings.ini \
    update_firmware.sh
