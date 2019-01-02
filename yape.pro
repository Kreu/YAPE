TEMPLATE = app
CONFIG += debug
QT += core gui widgets

INCLUDEPATH += $$PWD/include \
               $$PWD/include/gui

HEADERS +=  ./include/gui/mainwindow.h \
            ./include/gui/sequence_textbox.h \
            ./include/gui/newfeature_window.h
SOURCES +=  ./src/yape.cc \
            ./src/gui/mainwindow.cc \
            ./src/gui/sequence_textbox.cc \
            ./src/gui/newfeature_window.cc
