#include "services.h"
#include "include.h"

#include <QJsonObject>

ServicesInstance*  ServicesInstance::_instance = 0;

ServicesInstance*  ServicesInstance::Instance()
{
    if (0 == _instance) {
        _instance = new ServicesInstance();
    }
    return _instance;
}

ServicesInstance::ServicesInstance() :
    mqttinstance(MqttSubInstance::Instance()),
    mysqlinstance(MysqlInterfaceInstance::Instance()),
    mailsmtpinstance(MailSmtpInstance::Instance()),
    smsinstance(TencentsmsInstance::Instance()),
    celllocationinstance(Celllocationinstance::Instance())
{

    QObject::connect(mqttinstance, SIGNAL(Signals_Server_Init()), mysqlinstance, SLOT(Slots_Server_Init()));
    QObject::connect(mqttinstance, SIGNAL(Signals_Machine_Connected(QString)), mysqlinstance, SLOT(Slots_Machine_Connected(QString)));
    QObject::connect(mqttinstance, SIGNAL(Signals_Machine_Disconnected(QString)), mysqlinstance, SLOT(Slots_Machine_Disconnected(QString)));
    QObject::connect(mqttinstance, SIGNAL(Signals_ChkErrDataReceived(QString, QJsonDocument)), this, SLOT(Slots_ChkErrDataReceived(const QString, QJsonDocument)));
    QObject::connect(mqttinstance, SIGNAL(Signals_PositionReceived(QString, uint, int, int, uint, uint)), this, SLOT(Slots_PositionReceived(const QString, uint, int, int, uint, uint)));
}

ServicesInstance::~ServicesInstance()
{

}

void ServicesInstance::Slots_ChkErrDataReceived(const QString mid, QJsonDocument document)
{
    QJsonObject obj = document.object();

    QString mtype = mid.left(1);
    QString machineid = mid.right(6);
    qint16 panelid = obj["panelid"].toInt();
    QString panel = m_panelinfo.getCNName(panelid);
    QString lot = obj["panellot"].toString();
    QString error = obj["summary"].toString();
    qint32 errorcode = obj["errcode"].toInt();
    QString datetime = QDateTime::fromTime_t(obj["chkdatetime"].toInt()).toString("yy-MM-dd HH:mm");
    if (panelid < 50) {
        mtype += 'M';
    } else {
        mtype += 'V';
    }
    QString string = "<table>";
    string += QString("<tr> <td> mtype </td> <td> %1 </td> </tr>").arg(mtype);
    string += QString("<tr> <td> machineid </td> <td> %1 </td> </tr>").arg(machineid);
    string += QString("<tr> <td> panel </td> <td> %1 </td> </tr>").arg(panel);
    string += QString("<tr> <td> datetime </td> <td> %1 </td> </tr>").arg(datetime);
    string += QString("<tr> <td> lot </td> <td> %1 </td> </tr>").arg(lot);
    string += QString("<tr> <td> error </td> <td> %1 </td> </tr>").arg(error);
    string += "</table>";
    mailsmtpinstance->sendmail(string, "new CMD_CHKERRDATA");
    QStringList strlist, phonelist;
    strlist << machineid << m_panelinfo.parseError(errorcode) << panel << lot << datetime;

    smsinstance->setApp((QString) TENCENTSMS_APPID, (QString) TENCENTSMS_APPKEY);

    phonelist << PHONE1 << PHONE2 << PHONE3;
    qDebug() << smsinstance->send(phonelist, (qint32) TENCENTSMS_TPLID, strlist);

}

void ServicesInstance::Slots_PositionReceived(const QString mid, uint, int mcc, int mnc, uint lac, uint ci)
{
    QString machineid = mid.right(6);
    if (mcc == 0)
        mcc = 460;
    if (mnc == 0)
        mnc = 1;
    QString mtype;
    uint oldlac,oldci;
    if (!mysqlinstance->getMachine(machineid, mtype)) {
        return;
    }
    if (mysqlinstance->getNewpos(machineid, oldlac, oldci)) {
        if(oldlac == lac && qAbs(oldci - ci) < 2){
            qDebug() << "no need to update";
            return;
        }
    }
    celllocationinstance->getlocation(mcc, mnc, lac, ci);
    mysqlinstance->setNewpos(machineid, mcc, mnc, lac, ci, celllocationinstance->getLat(), celllocationinstance->getLon() ,celllocationinstance->getAddress());

}
