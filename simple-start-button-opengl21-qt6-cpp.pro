QT += core gui openglwidgets widgets
win32: LIBS += -lopengl32
SOURCES += main.cpp
TARGET = app
