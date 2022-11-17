# -------------------------------------------------
# Project created by QtCreator 2009-12-19T15:32:55
# -------------------------------------------------
QT += opengl \
    svg \
    webkit \
    xml
TARGET = PlottingDemo
TEMPLATE = app
SOURCES += Main.cpp \
    MainWindow.cpp \
    GraphWindow.cpp \
    GraphWidget.cpp \
    AddGraphDialog.cpp \
    TrackBall.cpp \
    BrowserWindow.cpp
HEADERS += MainWindow.h \
    DataStruct.h \
    GraphWindow.h \
    GraphWidget.h \
    AddGraphDialog.h \
    Vector3.h \
    TrackBall.h \
    BrowserWindow.h
FORMS += MainWindow.ui \
    AddGraphDialog.ui \
    GraphWindow.ui \
    BrowserWindow.ui
