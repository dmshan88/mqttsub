#ifndef TENCENTSMSINSTANCE_H
#define TENCENTSMSINSTANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
static const QString TENCENTSMS_URL = "https://yun.tim.qq.com/v5/tlssmssvr/sendmultisms2";

class TencentsmsInstance : public QObject
{
    Q_OBJECT
public:
    static TencentsmsInstance* Instance();
    ~TencentsmsInstance();
    void setApp(QString appid, QString appkey);
    bool send(QStringList phonelist, qint32 tplid, QStringList params, QString sign = "", QString extend = "", QString ext = "");

private:
    QString hashauth(QString phone);
    bool checkreturn(QByteArray retdata);

//    QUrl getUrl();

protected:
    TencentsmsInstance();

signals:

public slots:

private slots:

private:
    static TencentsmsInstance* _instance;
    QString m_appkey;
    QString m_appid;
    QUrl m_url;
    qint32 m_rand;
    qint32 m_time;
};

#endif
