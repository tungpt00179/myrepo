#-------------------------------------------------
#
# Project created by QtCreator 2015-06-24T13:38:08
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = GuiDriver
TEMPLATE = app
CONFIG   -= app_bundle
unix:!macx:{
CONFIG += serialport
}


SOURCES += main.cpp\
    jobwidget.cpp \
    driverform.cpp \
    pendingjobwidget.cpp \
    historywidget.cpp

HEADERS  += \
    jobwidget.h \
    log.h \
    driverform.h \
    pendingjobwidget.h \
    historywidget.h

FORMS    += \
    jobwidget.ui \
    meterform.ui \
    driverform.ui \
    historywidget.ui
#QMAKE_CXXFLAGS += -std=c++11

#install_it.path = $$OUT_PWD/
#install_it.files += %{sourceDir}/config/settings.ini \
#    %{sourceDir}/images/unlock.png \
#    %{sourceDir}/cheap.db

#INSTALLS += install_it
#DISTFILES += \
#    config/settings.ini \
#    images/unlock.png \
#    cheap.db
RESOURCES +=

unix: LIBS += -L$$OUT_PWD/../network/ -lnetwork \
            -L$$OUT_PWD/../models/ -lmodels \
            -L$$OUT_PWD/../utils/ -lutils \
            -L /usr/local/lib/ -lqjson \



INCLUDEPATH += $$PWD/../network \
                $$PWD/../models \
                $$PWD/../utils \
                /usr/local/include/

DEPENDPATH += $$PWD/../network \
                $$PWD/../models \
                $$PWD/../utils \

unix: PRE_TARGETDEPS += $$OUT_PWD/../models/libmodels.a \
                        $$OUT_PWD/../utils/libutils.a \
                        $$OUT_PWD/../network/libnetwork.a \

unix:!macx: LIBS += -L$$OUT_PWD/../hardware/ -lhardware -lX11 -lgps \
            -lwiringPi

INCLUDEPATH += $$PWD/../hardware
DEPENDPATH += $$PWD/../hardware
LIBS += -L$$OUT_PWD/../hardware/ -lhardware
PRE_TARGETDEPS += $$OUT_PWD/../hardware/libhardware.a


unix: LIBS += -L$$OUT_PWD/../CheapDB/ -lCheapDB

INCLUDEPATH += $$PWD/../CheapDB
DEPENDPATH += $$PWD/../CheapDB

unix: PRE_TARGETDEPS += $$OUT_PWD/../CheapDB/libCheapDB.a

DISTFILES += \
    config/settings.ini

OTHER_FILES += \
    config/settings.ini
