#include "tencentsmsinstance.h"
#include "httppostinstance.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QUrl>
#include <QUrlQuery>
#include <QDateTime>
#include <QDebug>


TencentsmsInstance*  TencentsmsInstance::_instance = 0;

TencentsmsInstance*  TencentsmsInstance::Instance()
{
    if (0 == _instance) {
        _instance = new TencentsmsInstance();
    }
    return _instance;
}

TencentsmsInstance::TencentsmsInstance()
{
}

TencentsmsInstance::~TencentsmsInstance()
{

}

void TencentsmsInstance::setApp(QString appid, QString appkey)
{
    m_appid = appid;
    m_appkey = appkey;

}

QString TencentsmsInstance::hashauth(QString phone)
{
    m_time = QDateTime::currentDateTime().toTime_t();
    qsrand(m_time);
    m_rand = qrand();
    QUrlQuery urlquery;
    urlquery.addQueryItem("sdkappid", m_appid);
    urlquery.addQueryItem("random", QString::number(m_rand));
    m_url = TENCENTSMS_URL;
    m_url.setQuery(urlquery);

    QString hashstring = QString("appkey=%1&random=%2&time=%3&mobile=%4").arg(m_appkey).arg(m_rand).arg(m_time).arg(phone);
    return QCryptographicHash::hash(hashstring.toLatin1(),QCryptographicHash::Sha256).toHex();

}

bool TencentsmsInstance::send(QStringList phonelist, qint32 tplid, QStringList params, QString sign, QString extend, QString ext)
{

    QString phonehash;
    QJsonObject json,tel;
    QJsonArray telarr;
    for (int i = 0; i < phonelist.size(); ++i) {
        tel.insert("mobile", phonelist.at(i));
        tel.insert("nationcode", (QString)"86");
        telarr.append(tel);
        phonehash.append(phonelist.at(i));
        if (i < phonelist.size()-1)
            phonehash.append(',');
    }

    json.insert("tel",telarr);
    json.insert("params", QJsonArray::fromStringList(params));
    json.insert("sig", hashauth(phonehash));
    json.insert("time", m_time);
    json.insert("tpl_id", tplid);
    json.insert("ext", ext);
    json.insert("extend", extend);
    json.insert("sign", sign);

    HttpPostInstance* http = HttpPostInstance::Instance();
    http->setRawHeader("Content-Type","application/json; charset=utf-8");
    http->setUrl(m_url);
    qDebug() << "sms to " << phonehash;
    return checkreturn(http->post(QJsonDocument(json).toJson()));


}

bool TencentsmsInstance::checkreturn(QByteArray retdata)
{
    QJsonDocument retjsondoc;
    QJsonObject retjsonobj;
    if (!retdata.isEmpty()) {
        retjsondoc = QJsonDocument::fromJson(retdata);
        if (retjsondoc.isObject()) {
            retjsonobj = retjsondoc.object();
            if(retjsonobj.contains("result") && retjsonobj["result"] == QJsonValue(0)) {
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
