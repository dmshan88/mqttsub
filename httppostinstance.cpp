#include <QUrl>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkReply>
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
    request(new QNetworkRequest())
{

}

HttpPostInstance::~HttpPostInstance()
{

}

QNetworkRequest* HttpPostInstance::getRequest()
{
    return request;
}

QByteArray HttpPostInstance::post(QByteArray data)
{
    QByteArray bytes;
    QEventLoop temp_loop;

    QNetworkReply* reply = nam->post(*request, data);
    connect(reply, SIGNAL(finished()), &temp_loop, SLOT(quit()));
    temp_loop.exec();
    if (reply->error() == QNetworkReply::NoError)
    {
         bytes = reply->readAll();
    }
    reply->deleteLater();
    return bytes;

}

QByteArray HttpPostInstance::get()
{
    QByteArray bytes;
    QEventLoop temp_loop;

    QNetworkReply* reply = nam->get(*request);
    connect(reply, SIGNAL(finished()), &temp_loop, SLOT(quit()));
    temp_loop.exec();
    if (reply->error() == QNetworkReply::NoError)
    {
         bytes = reply->readAll();
    }
    reply->deleteLater();
    return bytes;

}

void HttpPostInstance::setRawHeader(const QByteArray &headerName, const QByteArray &headerValue)
{
    request->setRawHeader(headerName,headerValue);

}

void HttpPostInstance::setUrl(const QUrl &url)
{
    request->setUrl(url);
}
