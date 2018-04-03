#include <QDateTime>
#include <QByteArray>
#include <QString>
#include <QDataStream>
//#include <QUrl>
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
    m_client(new QMQTT::Client()),
    m_post(HttpPostInstance::Instance())
{
    connect(m_client, SIGNAL(connected()), this, SLOT(Slots_MQTT_Connected()));
    connect(m_client, SIGNAL(subscribed(QString)), this, SLOT(Slots_MQTT_subscribed(QString)));
    connect(m_client, SIGNAL(received(QMQTT::Message)), this, SLOT(Slots_MQTT_Received(QMQTT::Message)));
//    QObject::connect(&c1, &MyClient1::disconnected, &s1, &Logger::showDisConnected);
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
    m_client->subscribe("mnchip_mqtt_server", 2);
    m_client->subscribe("$SYS/broker/clients/total", 0);
    m_client->subscribe("$SYS/broker/clients/connected", 0);
    m_client->subscribe("$SYS/broker/subscriptions/count", 0);

    m_post->mypost(HttpPostInstance::CMD_INIT);
//    QByteArray postdata;
//    postdata.append("cmd=init&");
//    postdata.append((QString) "clientid=1" + (QString) MYMQTT_CLIENT_ID);
//    reply = nam->post(*request, postdata);
}

void MqttSubInstance::Slots_MQTT_subscribed(const QString &topic)
{
    qDebug() << topic << "subscribed";
}

void MqttSubInstance::Slots_MQTT_Received(QMQTT::Message message)
{
//    qDebug() << message.payload();
    qDebug() << QDateTime::currentDateTime().toString("yy-MM-dd HH:mm:ss") << " received:";
//    QByteArray postdata;
    QString data(message.payload());
    QString mid;
    if (message.topic() != "mnchip_mqtt_server") {
        qDebug() << "topic:" << message.topic() << data;
        return ;
    }
    if (data.startsWith("CMD_DISCONNECT")) {
//        postdata.append("cmd=disconnect&");
//        postdata.append("mid=" + data.mid(26));
//        reply = nam->post(*request, postdata);
        mid = data.mid(26);
        m_post->mypost(HttpPostInstance::CMD_DISCONNECT, mid);
        qDebug() << "CMD_DISCONNECT" << mid;
        return ;
    }

    QByteArray inBlock = message.payload();
/*
    if (inBlock.startsWith(CMD_DISCONNECT.toLatin1()))
    {
//                ParseDisconnect(inBlock);
        qDebug() << "disconnect" << inBlock.to;
        return;
    }
*/
    QDataStream in(&inBlock, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_7);
    QString cmdtype;
    in >> cmdtype;

    if ((QString::compare(cmdtype, CMD_MACHINEINFO, Qt::CaseSensitive)) == 0)
    {
//      qDebug() << "CMD_MACHINEINFO";
        QString clientid;
        in >> clientid;
//        postdata.append("cmd=connected&");
//        postdata.append("mid=" + clientid.mid(12));
//        reply = nam->post(*request, postdata);
        mid = clientid.mid(12);
        m_post->mypost(HttpPostInstance::CMD_CONNECTED, mid);
        qDebug() << "CMD_MACHINEINFO" << mid;

    }
    else if ((QString::compare(cmdtype, CMD_LOGINPSD, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_LOGINPSD";
    }
    else if ((QString::compare(cmdtype, CMD_LOGINPSD_VERIFY, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_LOGINPSD_VERIFY";
    }
    else if ((QString::compare(cmdtype, CMD_ROOTPATH, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_ROOTPATH";

    }
    else if ((QString::compare(cmdtype, CMD_PATHFILE, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_PATHFILE";
    }
    else if ((QString::compare(cmdtype, CMD_FILE_DOWNLOAD_TO_SERVER, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_FILE_DOWNLOAD_TO_SERVER";
    }
    else if ((QString::compare(cmdtype, CMD_PING, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_PING";
    }
    //else if ((QString::compare(cmdtype, CMD_DISCONNECT, Qt::CaseSensitive)) == 0)
    //{
    //	ParseDisconnect(in);
    //}
    else if ((QString::compare(cmdtype, CMD_FILE_UPLOAD_TO_SERVER, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_FILE_UPLOAD_TO_SERVER";
    }
    else if (QString::compare(cmdtype, CMD_FILE_DELETE_SUCCESS, Qt::CaseSensitive) == 0)
    {
        qDebug() << "CMD_FILE_DELETE_SUCCESS";
    }
    else if (QString::compare(cmdtype, CMD_CHKRESULT, Qt::CaseSensitive) == 0)
    {
        qDebug() << "CMD_CHKRESULT";
    }
    else if (QString::compare(cmdtype, CMD_PATIENTINFO, Qt::CaseSensitive) == 0)
   {
       qDebug() << "CMD_PATIENTINFO";
   }
    else if (QString::compare(cmdtype, CMD_TMPDATA_FILES, Qt::CaseSensitive) == 0)
    {
        qDebug() << "CMD_TMPDATA_FILES";
    }
    else if (QString::compare(cmdtype, CMD_CHKERRDATA, Qt::CaseSensitive) == 0)
    {
        qDebug() << "CMD_CHKERRDATA";
    }
    else if (QString::compare(cmdtype, CMD_ADJUSTTEMP_GET, Qt::CaseSensitive) == 0)
    {
        qDebug() << "CMD_ADJUSTTEMP_GET";
    }
    else if (QString::compare(cmdtype, CMD_RESETTIME, Qt::CaseInsensitive) == 0)
    {
        qDebug() << "CMD_RESETTIME";
    }
    else if (QString::compare(cmdtype, CMD_POSITION, Qt::CaseSensitive) == 0)
    {
        qDebug() << "CMD_POSITION";
    }
    else if ((QString::compare(cmdtype, CMD_MACHINEERRDATA, Qt::CaseSensitive)) == 0)
    {
        qDebug() << "CMD_MACHINEERRDATA";
    }
    else if (QString::compare(cmdtype, CMD_QCRESULT, Qt::CaseSensitive) == 0)
    {
        qDebug() << "CMD_QCRESULT";
    }
    else
    {
        qDebug() << "OTHER:" << inBlock;
    }
}
