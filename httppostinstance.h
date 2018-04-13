#ifndef HTTPPOSTINSTANCE_H
#define HTTPPOSTINSTANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class HttpPostInstance : public QObject
{
    Q_OBJECT
public:
    static HttpPostInstance *Instance();
    ~HttpPostInstance();
    QNetworkRequest* getRequest();

    QByteArray post(QByteArray data);
    QByteArray get();
    void setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    void setUrl(const QUrl & url);
private:

protected:
    HttpPostInstance();

signals:

public slots:

private slots:

private:
    static HttpPostInstance* _instance;
    QNetworkAccessManager* nam;
    QNetworkRequest* request;
};

#endif
