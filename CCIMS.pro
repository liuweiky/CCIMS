#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T19:33:51
#
#-------------------------------------------------

QT += core gui
QT += widgets
QT += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CCIMS
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    jsonxx.cpp \
    ccmis.cpp \
    info_table.cpp \
    shopmainwindow.cpp \
    usermainwindow.cpp \
    shopsearchwindow.cpp \
    shopservicewindow.cpp \
    placemainwindow.cpp \
    administratormainwindow.cpp \
    administratorleadwindow.cpp \
    administratorscwindow.cpp \
    usersearchwindow.cpp \
    userrechargewindow.cpp

HEADERS += \
    mainwindow.h \
    jsonxx.h \
    user.h \
    shop.h \
    information.h \
    ccmis.h \
    info_table.h \
    shopmainwindow.h \
    usermainwindow.h \
    shopsearchwindow.h \
    shopservicewindow.h \
    placemainwindow.h \
    administratormainwindow.h \
    administratorleadwindow.h \
    administratorscwindow.h \
    usersearchwindow.h \
    userrechargewindow.h \
    usersfwindow.h \
    common_funcs.h

FORMS += \
    mainwindow.ui \
    info_table.ui \
    shopmainwindow.ui \
    usermainwindow.ui \
    shopsearchwindow.ui \
    shopservicewindow.ui \
    placemainwindow.ui \
    administratormainwindow.ui \
    administratorleadwindow.ui \
    administratorscwindow.ui \
    usersearchwindow.ui \
    userrechargewindow.ui
