#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T19:33:51
#
#-------------------------------------------------

QT += core gui
QT += widgets

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
    superusermainwindow.cpp \
<<<<<<< HEAD
    usermainwindow.cpp
=======
    info_table.cpp
>>>>>>> c4551380f23154324a09751b2448325f7944bf6f

HEADERS += \
        mainwindow.h \
        jsonxx.h \
        user.h \
        shop.h \
        information.h \
        ccmis.h \
    superusermainwindow.h \
<<<<<<< HEAD
    usermainwindow.h
=======
    info_table.h
>>>>>>> c4551380f23154324a09751b2448325f7944bf6f

FORMS += \
        mainwindow.ui \
    superusermainwindow.ui \
<<<<<<< HEAD
    usermainwindow.ui
=======
    info_table.ui
>>>>>>> c4551380f23154324a09751b2448325f7944bf6f
