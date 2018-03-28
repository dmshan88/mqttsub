#include <QDateTime>
#include "mqttsubinstance.h"
#include "include.h"

MqttSubInstance*  MqttSubInstance::_instance = 0;

MqttSubInstance*  MqttSubInstance::Instance()
{
    if (0 == _instance) {
        _instance = new MqttSubInstance();
    }
    return _instance;
}

MqttSubInstance::MqttSubInstance() :
    m_client(new QMQTT::Client())
{
    connect(m_client, SIGNAL(connected()), this, SLOT(Slots_MQTT_Connected()));
//    QObject::connect(&c1, &MyClient1::connected, &s1, &Logger::showConnected);
//    QObject::connect(&c1, &MyClient::connected, &c1, &MyClient1::subscribeTo);
//    QObject::connect(&c1, &MyClient1::disconnected, &s1, &Logger::showDisConnected);
//    QObject::connect(&c1, &MyClient1::subscribed, &s1, &Logger::showSubscribed);
//    QObject::connect(&c1, &MyClient1::received, &s1, &Logger::showMqttData);
//    QObject::connect(&a, &QCoreApplication::aboutToQuit, &c1, &MyClient1::Disconnect);
    m_client->setHost(MYMQTT_SERVER);
    m_client->setPort(MYMQTT_SERVER_PORT);
    m_client->setClientId(MYMQTT_CLIENT_ID);
    m_client->setUsername(MYMQTT_USERNAME);
    m_client->setPassword(MYMQTT_PASSWORD);
//    qDebug() << QDateTime::currentDateTime().toString("yy-MM-dd HH:mm:ss") << " start connect to server";
    m_client->Connect();
}

MqttSubInstance::~MqttSubInstance()
{

}

void MqttSubInstance::Slots_MQTT_Connected()
{
    qDebug()<< QDateTime::currentDateTime().toString("yy-MM-dd HH:mm:ss") << "server connected";
}
