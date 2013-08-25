#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T16:33:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graph_editor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    graphscene.cpp \
    graphedge.cpp \
    graphnode.cpp \
    graphview.cpp \
    graphmodel.cpp \
    graphvisedge.cpp \
    graphvisnode.cpp \
    grmlsaver.cpp

HEADERS  += mainwindow.h \
    graphscene.h \
    graphedge.h \
    graphnode.h \
    graphview.h \
    graphmodel.h \
    graphitem.h \
    graphvisedge.h \
    graphvisnode.h \
    grmlsaver.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc

unix:!macx: LIBS += -ltinyxml2
