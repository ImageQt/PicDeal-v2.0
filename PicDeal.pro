#-------------------------------------------------
#
# Project created by QtCreator 2016-01-03T19:22:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PicDeal
TEMPLATE = app

INCLUDEPATH += D:\opencv\x64-build\include \
               D:\opencv\x64-build\include\opencv \
               D:\opencv\x64-build\include\opencv2 \

SOURCES += main.cpp\
        picdealmain.cpp \
    qavgdialog.cpp \
    qfildialog.cpp \
    qcondialog.cpp \
    qcannydialog.cpp \
    qcannyshwdialog.cpp \
    qpescoldialog.cpp \
    qfftdialog.cpp \
    qroldialog.cpp \
    qzoomdialog.cpp \
    qcutdialog.cpp \
    core.cpp

HEADERS  += picdealmain.h \
    qavgdialog.h \
    qfildialog.h \
    qcondialog.h \
    qcannydialog.h \
    qcannyshwdialog.h \
    qpescoldialog.h \
    qfftdialog.h \
    qroldialog.h \
    qzoomdialog.h \
    qcutdialog.h \
    core.h

FORMS    += picdealmain.ui \
    qavgdialog.ui \
    qfildialog.ui \
    qcondialog.ui \
    qcannydialog.ui \
    qcannyshwdialog.ui \
    qpescoldialog.ui \
    qfftdialog.ui \
    qroldialog.ui \
    qzoomdialog.ui \
    qcutdialog.ui

RESOURCES += \
    picdealsrc.qrc

LIBS += D:\opencv\x64-build\x64\vc14\staticlib\IlmImf.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\libjasper.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\libjpeg.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\libpng.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\libtiff.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\libwebp.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_calib3d300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_core300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_features2d300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_flann300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_hal300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_highgui300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_imgcodecs300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_imgproc300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_ml300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_objdetect300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_photo300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_shape300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_stitching300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_superres300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_ts300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_video300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_videoio300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_videostab300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\opencv_world300.lib \
        D:\opencv\x64-build\x64\vc14\staticlib\zlib.lib

