#ifndef CELLLOCATIONINSTANCE_H
#define CELLLOCATIONINSTANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
static const QString CELLLOCATION_URL = "http://api.cellocation.com:81/cell/";

class Celllocationinstance : public QObject
{
    Q_OBJECT
public:
    static Celllocationinstance* Instance();
    ~Celllocationinstance();
    bool getlocation(int mcc, int mnc, uint lac, uint ci);

    double getLat() {return m_lat;}
    double getLon() {return m_lon;}
    QString getAddress() {return m_address;}
private:

    bool checkreturn(QByteArray retdata);
protected:
    Celllocationinstance();

signals:

public slots:

private slots:

private:
    static Celllocationinstance* _instance;
    double m_lat;
    double m_lon;
    QString m_address;
};

#endif
