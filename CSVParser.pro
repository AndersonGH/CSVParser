TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        csvfile.cpp \
        main.cpp

HEADERS += \
    csvfile.h

DISTFILES += \
    test.csv
