#include <QUrl>
#include <QDebug>
#include "include.h"
#include "httppostinstance.h"

HttpPostInstance*  HttpPostInstance::_instance = 0;

HttpPostInstance*  HttpPostInstance::Instance()
{
    if (0 == _instance) {
        _instance = new HttpPostInstance();
    }
    return _instance;
}

HttpPostInstance::HttpPostInstance() :
    nam(new QNetworkAccessManager()),
    request(new QNetworkRequest((QUrl) MYPOST_URL))
{
    request->setRawHeader("Content-Type","application/x-www-form-urlencoded");

}

HttpPostInstance::~HttpPostInstance()
{

}

void HttpPostInstance::mypost(const qint16 cmd, QVariant param1, QVariant param2, QVariant param3)
{
//    qDebug() << cmd << param1 << param2 << param3;
    QByteArray postdata;
    QString tmpstring = "";
    switch (cmd) {
        case CMD_INIT :
            qDebug() << "init!!!";
            tmpstring = "cmd=" + QString::number(cmd) + '&';
            postdata.append(tmpstring);
            tmpstring = "clientid=" + (QString) MYMQTT_CLIENT_ID;
            postdata.append(tmpstring);
            break;

        case CMD_CONNECTED :
            qDebug() << param1 << "conected!!!";
            tmpstring = "cmd=" + QString::number(cmd) + '&';
            postdata.append(tmpstring);
            tmpstring = "mid=" + param1.toString();
            postdata.append(tmpstring);
            break;

        case CMD_DISCONNECT :
            qDebug() << param1 << "disconnect!!!";
            tmpstring = "cmd=" + QString::number(cmd) + '&';
            postdata.append(tmpstring);
            tmpstring = "mid=" + param1.toString();
            postdata.append(tmpstring);
            break;

        default:
            return;
//            break;
    }
    reply = nam->post(*request, postdata);
    qDebug() << postdata;
}
