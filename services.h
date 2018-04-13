#ifndef SERVICES_H
#define SERVICES_H

#include <QObject>

#include "mqttsubinstance.h"
#include "mysqlinterface.h"
#include "mailsmtpinstance.h"
#include "tencentsmsinstance.h"
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

private:
    static ServicesInstance *_instance;
    MqttSubInstance *mqttinstance;
    MysqlInterfaceInstance *mysqlinstance ;
    MailSmtpInstance *mailsmtpinstance;
    TencentsmsInstance *smsinstance;
    Panelinfo m_panelinfo;


};
#endif
