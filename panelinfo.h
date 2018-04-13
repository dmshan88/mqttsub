#ifndef PANELINFO_H
#define PANELINFO_H

#include <QString>
#include <QMap>
class Panelinfo
{
public:

    Panelinfo();
    QString getCNName(qint16 id);
    QString parseError(qint32 errcode);

private:
    QMap<qint16, QString> cnnamemap;
    QMap<qint16, QString> errmap;
};

#endif
