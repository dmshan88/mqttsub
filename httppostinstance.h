#ifndef HTTPPOSTINSTANCE_H
#define HTTPPOSTINSTANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QVariant>
//#include <QINT

class HttpPostInstance : public QObject
{
    Q_OBJECT
public:
    static HttpPostInstance *Instance();
    ~HttpPostInstance();
//    void mypost(const qint16 cmd, QVariant param1 = "", QVariant param2 = "", QVariant param3 = "");

public:
    static const qint16 CMD_INIT = 1;
    static const qint16 CMD_CONNECTED = 2;
    static const qint16 CMD_DISCONNECT = 3;
//    static const qint8 CMD_INIT = 0;
//    static const qint8 CMD_INIT = 0;

protected:
    HttpPostInstance();

signals:

public slots:

private slots:

private:
    static HttpPostInstance *_instance;
    QNetworkAccessManager *nam;
    QNetworkRequest *request;
    QNetworkReply *reply;
};

#endif
