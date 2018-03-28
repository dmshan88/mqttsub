#include <QCoreApplication>
#include <QDebug>

#include "qmqtt/qmqtt.h"
#include "include.h"
using QMQTT::Client;

int main(int argc, char ** argv)
{
    QCoreApplication a(argc, argv);
    Client *client = new Client("localhost", 1883);
    qDebug() << client->isConnected() << POST_URL;
    return a.exec();
}
