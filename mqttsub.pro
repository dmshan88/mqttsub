QT += network
QT -= gui

CONFIG += console
TARGET = mqttsub
TEMPLATE = app

DEFINES += PARAMS_LOCAL

SOURCES += main.cpp \
    mqttsubinstance.cpp \
    httppostinstance.cpp \
    qmqtt/qmqtt_client.cpp \
    qmqtt/qmqtt_network.cpp \
    qmqtt/qmqtt_frame.cpp \
    qmqtt/qmqtt_client_p.cpp\
    qmqtt/qmqtt_message.cpp \
    qmqtt/qmqtt_will.cpp

HEADERS += include.h \
    mqttsubinstance.h \
    httppostinstance.h \
    params.h \
    params_local.h \
    qmqtt/qmqtt_client.h \
    qmqtt/qmqtt_global.h \
    qmqtt/qmqtt_network.h \
    qmqtt/qmqtt_frame.h \
    qmqtt/qmqtt_client_p.h \
    qmqtt/qmqtt_message.h \
    qmqtt/qmqtt_will.h \
    qmqtt/qmqtt.h
