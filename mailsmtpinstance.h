#ifndef MAILSMTPINSTANCE_H
#define MAILSMTPINSTANCE_H

#include <QObject>
#include <QJsonDocument>

#include "smtpclient/SmtpMime"
#include "include.h"

class MailSmtpInstance : public QObject
{
    Q_OBJECT
public:
    static MailSmtpInstance *Instance();
    ~MailSmtpInstance();
    bool sendmail(QString content, QString subject = "", QString mailto = MYSMTP_SENDT0);
protected:
    MailSmtpInstance();

private:
signals:

public slots:
//    void Slots_ChkErrDataReceived(const QString mid, QJsonDocument document);

private slots:


private:
    static MailSmtpInstance *_instance;
    SmtpClient *m_smtp;
};

#endif
