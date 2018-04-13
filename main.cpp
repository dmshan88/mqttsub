#include <QCoreApplication>
#include <QDebug>

#include "services.h"
#include "functions.h"
#include "panelinfo.h"
int main(int argc, char ** argv)
{
    qInstallMessageHandler(myMessageOutput);
    QCoreApplication a(argc, argv);
    ServicesInstance* instance = ServicesInstance::Instance();
    return a.exec();
}
