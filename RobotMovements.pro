#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T13:17:54
#
#-------------------------------------------------

QT += webkit core gui webkitwidgets network widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotMovements
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        map.cpp \
        aboutdialog.cpp \
    instructionsdialog.cpp \
    robotgriditem.cpp \
    robotgridmatrix.cpp \
    robotpath.cpp

HEADERS  += mainwindow.h \
        map.h \
        aboutdialog.h \
    instructionsdialog.h \
    robotgriditem.h \
    robotgridmatrix.h \
    robotpath.h

FORMS    += mainwindow.ui \
        aboutdialog.ui \
    instructionsdialog.ui

RESOURCES += \
    Icons.qrc
