TEMPLATE = app
CONFIG += debug c++1z
QT += core gui widgets

INCLUDEPATH += $$PWD/include \
               $$PWD/include/gui \
               $$PWD/include/models

HEADERS +=  ./include/gui/main_window_view.h \
            ./include//gui/sequence_view_model.h \
            ./include/gui/sequence_view.h \
            ./include/models/sequence_model.h \
            ./include/models/feature_model.h \
            ./include/gui/restriction_digest_view.h \
            ./include/json.h \
            ./include/gui/translate_view.h \
            ./include/gui/translate_view_model.h \
            ./include/oligo_analyser.h
SOURCES +=  ./src/yape.cc \
            ./src/gui/main_window_view.cc \
            ./src/gui/sequence_view_model.cc \
            ./src/gui/sequence_view.cc \
            ./src/models/sequence_model.cc \
            ./src/models/feature_model.cc \
            ./src/gui/restriction_digest_view.cc \
            ./src/json.cc \
            ./src/gui/translate_view.cc \
            ./src/gui/translate_view_model.cc \
            ./src/oligo_analyser.cc
