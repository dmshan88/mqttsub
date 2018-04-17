#ifndef MYSQLINTERFACE_H
#define MYSQLINTERFACE_H

#include <QObject>
#include <QSqlDatabase>


class MysqlInterfaceInstance : public QObject
{
    Q_OBJECT
public:
    static MysqlInterfaceInstance *Instance();
    ~MysqlInterfaceInstance();
    bool isOpen();

    bool addNewstat(QString mid, bool online = true);
    bool getMachine(QString mid, QString& mtype);
    bool getNewpos(QString mid, uint& lac, uint& ci);
    bool setNewpos(const QString mid, int mcc, int mnc, uint lac, uint ci, double lat, double lon, QString address);
private:


protected:
    MysqlInterfaceInstance();

signals:

public slots:
    void Slots_Server_Init();
    void Slots_Machine_Connected(const QString mid);
    void Slots_Machine_Disconnected(const QString mid);
//    void Slots_PositionReceived(const QString mid, uint, int mcc, int mnc, uint lac, uint ci);

private slots:

private:
    static MysqlInterfaceInstance *_instance;
    QSqlDatabase m_db;

};

#endif
