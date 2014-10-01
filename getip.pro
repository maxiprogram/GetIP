#-------------------------------------------------
#
# Project created by QtCreator 2014-08-20T10:26:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = getip
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainform.cpp \
    Class/smtp.cpp \
    Class/smtps.cpp

HEADERS  += \
    mainform.h \
    Class/smtp.h \
    Class/smtps.h

FORMS    += \
    mainform.ui

RESOURCES += \
    resource.qrc
