#include <QJsonObject>
#include <QDebug>
#include <QDateTime>
#include "mailsmsinstance.h"


MailSmsInstance*  MailSmsInstance::_instance = 0;

MailSmsInstance*  MailSmsInstance::Instance()
{
    if (0 == _instance) {
        _instance = new MailSmsInstance();
    }
    return _instance;
}

MailSmsInstance::MailSmsInstance() :
    m_smtp(new SmtpClient())
{
    m_smtp->setHost(MYSMTP_SERVER);
    m_smtp->setPort(MYSMTP_SERVER_PORT);
    m_smtp->setUser(MYSMTP_USERNAME);
    m_smtp->setPassword(MYSMTP_PASSWORD);
}

qint8 MailSmsInstance::sendmail(QString content, QString subject, QString mailto)
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
        return -1;
    }

    if (!m_smtp->login()) {
        qDebug() << "Failed to login!" << endl;
        return -2;
    }
    if (!m_smtp->sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
        return -3;
    }
    qDebug() << "sendmail";
    m_smtp->quit();
    return 0;
}


MailSmsInstance::~MailSmsInstance()
{

}


void MailSmsInstance::Slots_ChkErrDataReceived(const QString mid, QJsonDocument document)
{
    QJsonObject obj = document.object();

    QString mtype = mid.left(1);
    QString machineid = mid.right(6);
    qint16 panel = obj["panelid"].toInt();
    QString error = obj["summary"].toString();
    if (panel < 50) {
        mtype += 'M';
    } else {
        mtype += 'V';
    }
    QString string = "<table>";
    string += QString("<tr> <td> mtype </td> <td> %1 </td> </tr>").arg(mtype);
    string += QString("<tr> <td> machineid </td> <td> %1 </td> </tr>").arg(machineid);
    string += QString("<tr> <td> panel </td> <td> %1 </td> </tr>").arg(panel);
    string += QString("<tr> <td> error </td> <td> %1 </td> </tr>").arg(error);
    string += "</table>";
    sendmail(string, "CMD_CHKERRDATA");
}
