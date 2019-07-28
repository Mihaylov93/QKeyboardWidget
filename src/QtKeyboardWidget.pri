#-------------------------------------------------
#
# Project created by QtCreator 
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4){
    CONFIG += c++11
    QT += widgets
} else {
    QMAKE_CXXFLAGS += -std=c++11
}

#TARGET = qkeyboardwidget
#TEMPLATE = lib
#CONFIG+= shared

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
		$$PWD/keyboard.cpp \
		$$PWD/key.cpp \
		$$PWD/keylayout.cpp

HEADERS += \
                $$PWD/../include/keyboard.h \
                $$PWD/../include/key.h \
                $$PWD/../include/keylayout.h

DISTFILES += \
    en.json

RESOURCES += $$PWD/resource.qrc

INCLUDEPATH += \
    $$PWD/../include
