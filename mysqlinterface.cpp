#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDateTime>
#include <QDate>
#include <QSqlError>

#include "mysqlinterface.h"
#include "include.h"

MysqlInterfaceInstance*  MysqlInterfaceInstance::_instance = 0;

MysqlInterfaceInstance*  MysqlInterfaceInstance::Instance()
{
    if (0 == _instance) {
        _instance = new MysqlInterfaceInstance();
    }
    return _instance;
}

MysqlInterfaceInstance::MysqlInterfaceInstance()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(MYSQL_SERVER);
    m_db.setDatabaseName(MYSQL_DATABASE);
    m_db.setUserName(MYSQL_USERNAME);
    m_db.setPassword(MYSQL_PASSWORD);
    if (!m_db.open()) {
        qDebug("db not open");
    }
}

MysqlInterfaceInstance::~MysqlInterfaceInstance()
{

}

bool MysqlInterfaceInstance::isOpen()
{
    return m_db.isOpen();
}

void MysqlInterfaceInstance::Slots_Server_Init()
{
    QSqlQuery query;
    query.exec("TRUNCATE TABLE newstat");
    qDebug("server init");
}

void MysqlInterfaceInstance::Slots_Machine_Connected(const QString mid)
{
    qDebug() << "machine connect" << mid;
    addNewstat(mid);
}

void MysqlInterfaceInstance::Slots_Machine_Disconnected(const QString mid)
{
    qDebug() << "machine disconnect" << mid;
    addNewstat(mid, false);
}

bool MysqlInterfaceInstance::addNewstat(QString mid, bool online)
{
    if (mid.contains("unset")) {
        return false;
    }
    QString machineid = mid.right(6);
    QString onlinestat = online ? "Y" : "N";
    QString activetime = QDateTime::currentDateTime().toString("yy-MM-dd HH:mm:ss");
    QString errormsg;
    m_db.transaction();
    try {
        QSqlQuery q;
        q.prepare("SELECT * FROM machine WHERE id = :id");
        q.bindValue(":id", machineid);
        q.exec();
        switch (q.size()) {
        case 0 :
            qDebug() << "insert machine" << machineid;
            q.clear();
            q.prepare("INSERT INTO machine (id, clientid, mtype) VALUES (:id, :clientid, :mtype)");
            q.bindValue(":id", machineid);
            q.bindValue(":clientid", mid);
            q.bindValue(":mtype", mid.left(mid.length()-7));
            if (!q.exec()) {
                errormsg = "insert machine error";
                throw errormsg;
            }

            break;
        case 1 :

            break;
        default:
            errormsg = "machine error";
            throw errormsg;
            break;
        }
        qDebug() << "insert historystat" << machineid;
        q.clear();
        q.prepare("INSERT INTO historystat (machine_id, activetime, online) VALUES (:machine_id, :activetime, :online)");
        q.bindValue(":machine_id", machineid);
        q.bindValue(":activetime", activetime);
        q.bindValue(":online", onlinestat);
        if (!q.exec()) {
            errormsg = "insert historystat error";
            throw errormsg;
        }

        q.clear();
        q.prepare("SELECT * FROM newstat WHERE machine_id = :machine_id");
        q.bindValue(":machine_id", machineid);
        q.exec();
        switch (q.size()) {
        case 0 :
            q.clear();
            q.prepare("INSERT INTO newstat (machine_id, activetime, online) VALUES (:machine_id, :activetime, :online)");
            qDebug() << "insert newstat" << onlinestat;
            break;
        case 1 :
            q.prepare("UPDATE newstat SET activetime = :activetime , online = :online WHERE machine_id = :machine_id");
            qDebug() << "update newstat" << onlinestat;

            break;
        default:
            errormsg = " newstat error";
            throw errormsg;
            break;
        }
        q.bindValue(":machine_id", machineid);
        q.bindValue(":activetime", activetime);
        q.bindValue(":online", onlinestat);
        if (!q.exec()) {
            errormsg = "insert/update newstat error";
            throw errormsg;
        }
        m_db.commit();
        return true;
    } catch (QString exception){
        m_db.rollback();
        qDebug() << exception;
        return false;
    }

}

bool MysqlInterfaceInstance::getMachine(QString mid, QString &mtype)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM machine WHERE id = :id");
    q.bindValue(":id", mid);
    q.exec();
    switch (q.size()) {
    case 0 :
//        qDebug() << "0";
        return false;
        break;
    case 1 :
        q.next();
        mtype = q.value("mtype").toString();
        return true;
        break;
    default:
        qDebug() << "multi record";
        return false;
    }
}

bool MysqlInterfaceInstance::getNewpos(QString mid, uint &lac, uint& ci)
{
    qDebug() << "getNewpos" << mid << lac << ci;
    QSqlQuery q;
    q.prepare("SELECT * FROM newpos WHERE machine_id = :id");
    q.bindValue(":id", mid);
    q.exec();
    switch (q.size()) {
    case 0 :
        qDebug() << "0";
        return false;
        break;
    case 1 :
        qDebug() << "1";
        q.next();
        lac = q.value("lac").toInt();
        ci = q.value("ci").toInt();
        return true;
        break;
    default:
        qDebug() << "multi record";
        return false;
    }
}

bool MysqlInterfaceInstance::setNewpos(const QString mid, int mcc, int mnc, uint lac, uint ci, double lat, double lon, QString address)
{
    QSqlQuery q;
    uint oldlac, oldci;
    QString errormsg;
    m_db.transaction();
    try {
        if (!getNewpos(mid, oldlac, oldci)) {
            q.prepare("INSERT INTO newpos (machine_id, lastpostdate, mcc, mnc, lac, ci, lat, lon, address) VALUES (:machine_id, :lastpostdate, :mcc, :mnc, :lac, :ci, :lat, :lon, :address)");
            qDebug() << "insert newpos" << lac << ci;
        } else {
            q.prepare("UPDATE newpos SET lastpostdate = :lastpostdate , lac = :lac , ci = :ci , lat = :lat , lon = :lon , address = :address WHERE machine_id = :machine_id");
            qDebug() << "update newpos" << lac << ci;
        }

        q.bindValue(":machine_id", mid);
        q.bindValue(":lastpostdate", QDate::currentDate().toString("yyyy-MM-dd"));
        q.bindValue(":mcc", mcc);
        q.bindValue(":mnc", mnc);
        q.bindValue(":lac", lac);
        q.bindValue(":ci", ci);
        q.bindValue(":lat", lat);
        q.bindValue(":lon", lon);
        q.bindValue(":address", address);
        if(!q.exec()){
           errormsg = "setnewpos error";
            throw errormsg;
        }
        q.clear();
        q.prepare("INSERT INTO historypos (machine_id, activetime, lat, lon, address) VALUES (:machine_id, :activetime, :lat, :lon, :address)");
        q.bindValue(":machine_id", mid);
        q.bindValue(":activetime",  QDateTime::currentDateTime().toString("yy-MM-dd HH:mm:ss"));
        q.bindValue(":lat", lat);
        q.bindValue(":lon", lon);
        q.bindValue(":address", address);
        if (!q.exec()) {
            errormsg = "insert history newpos error";
            throw errormsg;
        }

        m_db.commit();
        return true;
    } catch (QString exception){
        m_db.rollback();
        qDebug() << exception;
        return false;
    }
}

