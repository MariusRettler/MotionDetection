#-------------------------------------------------
#
# Project created by QtCreator 2016-01-25T17:51:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MotionDetection
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_videoio
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann

SOURCES += main.cpp\
        mainwindow.cpp \
    imageserviceclass.cpp \
    matconverter.cpp \
    liveform.cpp \
    deadform.cpp

HEADERS  += mainwindow.h \
    imageserviceclass.h \
    matconverter.h \
    liveform.h \
    deadform.h \
    iform.h

FORMS    += mainwindow.ui \
    liveform.ui \
    deadform.ui
