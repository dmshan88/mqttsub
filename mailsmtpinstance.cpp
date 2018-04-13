#include <QJsonObject>
#include <QDebug>
#include <QDateTime>
#include "mailsmtpinstance.h"


MailSmtpInstance*  MailSmtpInstance::_instance = 0;

MailSmtpInstance*  MailSmtpInstance::Instance()
{
    if (0 == _instance) {
        _instance = new MailSmtpInstance();
    }
    return _instance;
}

MailSmtpInstance::MailSmtpInstance() :
    m_smtp(new SmtpClient())
{
    m_smtp->setHost(MYSMTP_SERVER);
    m_smtp->setPort(MYSMTP_SERVER_PORT);
    m_smtp->setUser(MYSMTP_USERNAME);
    m_smtp->setPassword(MYSMTP_PASSWORD);
}

MailSmtpInstance::~MailSmtpInstance()
{

}

bool MailSmtpInstance::sendmail(QString content, QString subject, QString mailto)
{
    MimeMessage message;

    EmailAddress sender(MYSMTP_USERNAME);
    message.setSender(&sender);

    EmailAddress to(mailto);
    message.addRecipient(&to);
    message.setSubject(subject);

//    MimeText text;
//    text.setText(content);
    MimeHtml html;
    html.setHtml(content);
    message.addPart(&html);

    if (!m_smtp->connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;
        return false;
    }

    if (!m_smtp->login()) {
        qDebug() << "Failed to login!" << endl;
        return false;
    }
    if (!m_smtp->sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
        return false;
    }
    qDebug() << "sendmail";
    m_smtp->quit();
    return true;
}
