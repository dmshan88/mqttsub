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
private:


protected:
    MysqlInterfaceInstance();

signals:

public slots:
    void Slots_Server_Init();
    void Slots_Machine_Connected(const QString mid);
    void Slots_Machine_Disconnected(const QString mid);

private slots:

private:
    static MysqlInterfaceInstance *_instance;
    QSqlDatabase m_db;

};

#endif
