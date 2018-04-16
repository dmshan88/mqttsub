QT += network
QT += sql
QT -= gui

CONFIG += console
TARGET = mqttsub
TEMPLATE = app

DEFINES += PARAMS_LOCAL

SOURCES += main.cpp \
    panelinfo.cpp \
    functions.cpp \
    services.cpp \
    mqttsubinstance.cpp \
    mysqlinterface.cpp \
    mailsmtpinstance.cpp \
    httppostinstance.cpp \
    tencentsmsinstance.cpp \
    celllocationinstance.cpp \
    qmqtt/qmqtt_client.cpp \
    qmqtt/qmqtt_network.cpp \
    qmqtt/qmqtt_frame.cpp \
    qmqtt/qmqtt_client_p.cpp\
    qmqtt/qmqtt_message.cpp \
    qmqtt/qmqtt_will.cpp \
    smtpclient/emailaddress.cpp \
    smtpclient/mimeattachment.cpp \
    smtpclient/mimefile.cpp \
    smtpclient/mimehtml.cpp \
    smtpclient/mimeinlinefile.cpp \
    smtpclient/mimemessage.cpp \
    smtpclient/mimepart.cpp \
    smtpclient/mimetext.cpp \
    smtpclient/smtpclient.cpp \
    smtpclient/quotedprintable.cpp \
    smtpclient/mimemultipart.cpp \
    smtpclient/mimecontentformatter.cpp

HEADERS += include.h \
    panelinfo.h \
    functions.h \
    services.h \
    mqttsubinstance.h \
    mysqlinterface.h \
    mailsmtpinstance.h \
    httppostinstance.h \
    tencentsmsinstance.h \
    celllocationinstance.h \
    params.h \
    params_local.h \
    qmqtt/qmqtt_client.h \
    qmqtt/qmqtt_global.h \
    qmqtt/qmqtt_network.h \
    qmqtt/qmqtt_frame.h \
    qmqtt/qmqtt_client_p.h \
    qmqtt/qmqtt_message.h \
    qmqtt/qmqtt_will.h \
    qmqtt/qmqtt.h \
    smtpclient/emailaddress.h \
    smtpclient/mimeattachment.h \
    smtpclient/mimefile.h \
    smtpclient/mimehtml.h \
    smtpclient/mimeinlinefile.h \
    smtpclient/mimemessage.h \
    smtpclient/mimepart.h \
    smtpclient/mimetext.h \
    smtpclient/smtpclient.h \
    smtpclient/SmtpMime \
    smtpclient/quotedprintable.h \
    smtpclient/mimemultipart.h \
    smtpclient/mimecontentformatter.h \
    smtpclient/smtpexports.h
