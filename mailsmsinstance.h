#ifndef MAILSMSINSTANCE_H
#define MAILSMSINSTANCE_H

#include <QObject>
#include <QJsonDocument>

#include "smtpclient/SmtpMime"
#include "include.h"

class MailSmsInstance : public QObject
{
    Q_OBJECT
public:
    static MailSmsInstance *Instance();
    ~MailSmsInstance();
protected:
    MailSmsInstance();

private:
    qint8 sendmail(QString content, QString subject = "", QString mailto = MYSMTP_SENDT0);
signals:

public slots:
    void Slots_ChkErrDataReceived(const QString mid, QJsonDocument document);

private slots:


private:
    static MailSmsInstance *_instance;
    SmtpClient *m_smtp;
};

#endif
