#ifndef COMMAND_H
#define COMMAND_H

#include <QMap>
#include <QString>
#include "../common.h"

//#define LOGIN_COMMAND(x,y,w,z) CommandFactory::createLoginNewCmd(x,y,w,z)

class Command
{
protected:
    QString m_command;
    QString m_data;
public:
    Command():m_command(""),m_data("{}"){}
    Command(QString command,QString data):m_command(command),m_data(data){}

    QString toString();
};

#endif // DEVICECOMMAND_H
