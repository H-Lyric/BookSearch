#-------------------------------------------------
#
# Project created by QtCreator 2019-01-24T14:35:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookSearch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        networker.cpp \
        book.cpp

HEADERS  += mainwindow.h \
        networker.h \
        book.h

FORMS    += mainwindow.ui

CONFIG += c++11

include (QZXing/QZXing.pri)
