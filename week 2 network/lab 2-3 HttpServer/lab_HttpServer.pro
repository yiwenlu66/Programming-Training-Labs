QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = lab_HttpServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    httpserver.cpp

HEADERS += \
    httpserver.h
