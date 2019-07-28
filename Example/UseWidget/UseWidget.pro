#-------------------------------------------------
# This is an example to be used as an entry point
# on how to use the keyboard widget.
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4){
    CONFIG += c++11
    QT += widgets
} else {
    QMAKE_CXXFLAGS += -std=c++11
}

TARGET = UseWidget
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Include the widget
include( $$PWD/../../QtKeyboardWidget.pro )
