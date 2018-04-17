#ifndef SERVICES_H
#define SERVICES_H

#include <QObject>
#include <QTimer>

#include "mqttsubinstance.h"
#include "mysqlinterface.h"
#include "mailsmtpinstance.h"
#include "tencentsmsinstance.h"
#include "celllocationinstance.h"
#include "panelinfo.h"

class ServicesInstance : public QObject
{
    Q_OBJECT
public:
    static ServicesInstance *Instance();
    ~ServicesInstance();
private:


protected:
    ServicesInstance();

signals:

public slots:


private slots:
    void Slots_ChkErrDataReceived(const QString mid, QJsonDocument document);
    void Slots_PositionReceived(const QString mid, uint, int mcc, int mnc, uint lac, uint ci);
    void recordstat();

private:
    static ServicesInstance *_instance;
    MqttSubInstance *mqttinstance;
    MysqlInterfaceInstance *mysqlinstance ;
    MailSmtpInstance *mailsmtpinstance;
    TencentsmsInstance *smsinstance;
    Celllocationinstance* celllocationinstance;
    Panelinfo m_panelinfo;
    QTimer* m_timer;


};
#endif
