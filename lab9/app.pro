TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(debug, debug|release)
{
LIBS += -L../objects/debug -lobjects
}
CONFIG(release, debug|release)
{
LIBS += -L../objects/release -lobjects
}

SOURCES += main.cpp
