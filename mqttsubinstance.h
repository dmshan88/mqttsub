#ifndef MQTTSUB_H
#define MQTTSUB_H

#include <QObject>
#include "qmqtt/qmqtt_client.h"
//using  QMQTT::Client;

class MqttSubInstance : public QObject
{
    Q_OBJECT
public:
    static MqttSubInstance *Instance();
    ~MqttSubInstance();

protected:
    MqttSubInstance();

signals:


//    MyClient(const QString & host, quint32 port) : QMQTT::Client(host, port) {
//    }

public slots:
//    void subscribeTo() {
//        subscribe("mnchip_mqtt_server", 2);
//        subscribe("$SYS/broker/clients/total", 0);
//        subscribe("$SYS/broker/clients/connected", 0);
//        subscribe("$SYS/broker/subscriptions/count", 0);
//    }
private slots:
    void Slots_MQTT_Connected();

private:
    static MqttSubInstance *_instance;
    QMQTT::Client *m_client;
};

#endif
