#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QMutex>

#include "qmqtt/qmqtt.h"
#include "mqttsubinstance.h"


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QByteArray localMsg = msg.toLocal8Bit();
    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
    }
    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString strMessage = QString(" DateTime:%1 Message:%2 File:%3  Line:%4  Function:%5 ")
            .arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);

    // 输出信息至文件中（读写、追加形式）
    QFile file("log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();
    // 解锁
    mutex.unlock();
}

int main(int argc, char ** argv)
{
    qInstallMessageHandler(myMessageOutput);
    QCoreApplication a(argc, argv);
//    MyClient *client = new MyClient("115.28.27.137", 1883);
    MqttSubInstance::Instance();
    return a.exec();
}
