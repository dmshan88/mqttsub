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

/*
void MailSmsInstance::Slots_ChkErrDataReceived(const QString mid, QJsonDocument document)
{
    QJsonObject obj = document.object();

    QString mtype = mid.left(1);
    QString machineid = mid.right(6);
    qint16 panel = obj["panelid"].toInt();
    QString lot = obj["lot"].toString();
    QString error = obj["summary"].toString();
    QString datetime = QDateTime::fromTime_t(obj["checkdatetime"].toInt()).toString("yy-MM-dd HH:mm");
    if (panel < 50) {
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
    sendmail(string, "CMD_CHKERRDATA");
    QStringList strlist, phonelist;
    strlist << machineid << error.left(8) << QString::number(panel) << lot << datetime;
    TencentsmsInstance* instance = TencentsmsInstance::Instance();
    instance->setApp("1400021595", "eca0d75539ba9202b0f6f5a8d8c1a504");
//   phonelist << "13820158461" << "18678318715";
    phonelist << "13820158461";
    qDebug() << instance->send(phonelist, 55384, strlist);

}
*/
