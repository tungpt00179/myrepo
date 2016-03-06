#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
#include "../common.h"

class CommandFactory
{
public:
    static QString createLoginCmd(QString imei_device,QString imei_sim,quint64 time);

    static QString createCommandGeneral(QString command, QString data="{}");

};
#endif // COMMANDFACTORY_H
