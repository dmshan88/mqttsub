#include <QCoreApplication>
#include <QDebug>

#include "qmqtt/qmqtt.h"
//#include "include.h"
#include "mqttsubinstance.h"
//using QMQTT::Client;

int main(int argc, char ** argv)
{
    QCoreApplication a(argc, argv);
//    MyClient *client = new MyClient("115.28.27.137", 1883);
    MqttSubInstance::Instance();
    return a.exec();
}
