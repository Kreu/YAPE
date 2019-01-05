TEMPLATE = app
CONFIG += debug c++1z
QT += core gui widgets

INCLUDEPATH += $$PWD/include \
               $$PWD/include/gui

HEADERS +=  ./include/gui/main_window_view.h \
            ./include/gui/sequence_textbox.h \
            ./include/gui/newfeature_window.h \
            ./include/sequence_view_model.h \
            ./include/sequence_model.h \
            ./include/gui/sequence_view.h
SOURCES +=  ./src/yape.cc \
            ./src/gui/main_window_view.cc \
            ./src/gui/sequence_textbox.cc \
            ./src/gui/newfeature_window.cc \
            ./src/sequence_view_model.cc \
            ./src/gui/sequence_view.cc
