#include "celllocationinstance.h"
#include "httppostinstance.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrl>
#include <QUrlQuery>
//#include <QDateTime>
#include <QDebug>


Celllocationinstance*  Celllocationinstance::_instance = 0;

Celllocationinstance*  Celllocationinstance::Instance()
{
    if (0 == _instance) {
        _instance = new Celllocationinstance();
    }
    return _instance;
}

Celllocationinstance::Celllocationinstance()
{
}

Celllocationinstance::~Celllocationinstance()
{

}

bool Celllocationinstance::getlocation(int mcc, int mnc, uint lac, uint ci)
{
    QUrlQuery urlquery;
    urlquery.addQueryItem("mcc", QString::number(mcc));
    urlquery.addQueryItem("mnc", QString::number(mnc));
    urlquery.addQueryItem("lac", QString::number(lac));
    urlquery.addQueryItem("ci", QString::number(ci));
    urlquery.addQueryItem("output", (QString)"json");

    QUrl url = CELLLOCATION_URL;
    url.setQuery(urlquery);
//    qDebug() << url;
    HttpPostInstance* http = HttpPostInstance::Instance();
//    http->setRawHeader("Content-Type","application/json; charset=utf-8");
    http->setUrl(url);
    return checkreturn(http->get());
}

bool Celllocationinstance::checkreturn(QByteArray retdata)
{
    QJsonDocument retjsondoc;
    QJsonObject retjsonobj;
    if (!retdata.isEmpty()) {
        retjsondoc = QJsonDocument::fromJson(retdata);
        if (retjsondoc.isObject()) {
            retjsonobj = retjsondoc.object();
            if(retjsonobj.contains("errcode") && retjsonobj["errcode"] == QJsonValue(0)) {
                m_lat = retjsonobj["lat"].toString().toDouble();
                m_lon = retjsonobj["lon"].toString().toDouble();
                m_address = retjsonobj["address"].toString();
//                qDebug() << "m_lat:" << m_lat << "m_lon:" << m_lon << "address:" << m_address;
                return true;
            } else {
                qDebug() << "retjsonobj error" << retjsonobj;
            }
        } else {
            qDebug() << "retjsondoc is not Object" << retjsondoc;
        }
    }
    return false;
}
