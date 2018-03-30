#ifndef MQTTSUBINSTANCE_H
#define MQTTSUBINSTANCE_H

#include <QObject>
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>
#include "httppostinstance.h"
#include "qmqtt/qmqtt_client.h"


static const QString CMD_DEVICEID						= "CMD_DEVICEID";
static const QString CMD_ROOTPATH						= "CMD_ROOTPATH";
static const QString CMD_PATHFILE						= "CMD_PATHFILE";
static const QString CMD_FILE_DOWNLOAD_TO_SERVER		= "CMD_FILE_DOWNLOAD_TO_SERVER";
static const QString CMD_FILE_UPLOAD_TO_CLIENT			= "CMD_FILE_UPLOAD_TO_CLIENT";
static const QString CMD_FILE_UPLOAD_TO_SERVER			= "CMD_FILE_UPLOAD_TO_SERVER";
static const QString CMD_RESTOREFAC					    = "CMD_RESTOREFAC";
static const QString CMD_MACHINEINFO					= "CMD_MACHINEINFO";
static const QString CMD_PING							= "CMD_PING";
static const QString CMD_DISCONNECT						= "CMD_DISCONNECT";
static const QString CMD_FILE_UPLOAD_TO_SERVER_SUCCESS  = "CMD_FILE_UPLOAD_TO_SERVER_SUCCESS";
static const QString CMD_FILE_DELETE                    = "CMD_FILE_DELETE";
static const QString CMD_FILE_DELETE_SUCCESS            = "CMD_FILE_DELETE_SUCCESS";
static const QString CMD_CHKRESULT						= "CMD_CHKRESULT";
static const QString CMD_TMPDATA_FILES					= "CMD_TMPDATA_FILES";
static const QString CMD_CHKERRDATA						= "CMD_CHKERRDATA";
static const QString CMD_TIMECALIBRATION                = "CMD_TIMECALIBRATION";
static const QString CMD_LOGINPSD                       = "CMD_LOGINPSD";
static const QString CMD_LOGINPSD_VERIFY                = "CMD_LOGINPSD_VERIFY";
static const QString CMD_ADJUSTTEMP_GET					= "CMD_ADJUSTTEMP_GET";
static const QString CMD_ADJUSTTEMP_SET			    	= "CMD_ADJUSTTEMP_SET";
static const QString CMD_RESETTIME                      = "CMD_RESETTIME";
static const QString CMD_PATIENTINFO                    = "CMD_PATIENTINFO";
static const QString CMD_POSITION                       = "CMD_POSITION";
static const QString CMD_MACHINEERRDATA                 = "CMD_MACHINEERRDATA";
static const QString CMD_QCRESULT						= "CMD_QCRESULT";

class MqttSubInstance : public QObject
{
    Q_OBJECT
public:
    static MqttSubInstance *Instance();
    ~MqttSubInstance();

protected:
    MqttSubInstance();

signals:

public slots:

private slots:
    void Slots_MQTT_Connected();
    void Slots_MQTT_subscribed(const QString &topic);
    void Slots_MQTT_Received(QMQTT::Message);

private:
    static MqttSubInstance *_instance;
    QMQTT::Client *m_client;
    HttpPostInstance *m_post;
//    QNetworkAccessManager *nam;
//    QNetworkRequest *request;
//    QNetworkReply *reply;
//    QString asdf;
};

#endif
