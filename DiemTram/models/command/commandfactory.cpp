#include "commandfactory.h"
#include "command.h"
#include <QVariant>
#include <QDebug>
#include <qjson/serializer.h>

QString CommandFactory::createLoginCmd(QString imei_device,
                                       QString imei_sim,
                                       quint64 time)
{
    QVariantMap deviceinfo;
    qDebug() << "factory dump:" << imei_device << imei_sim << time;
    deviceinfo.insert("imei_device",imei_device);
    deviceinfo.insert("imei_sim",imei_sim);
    deviceinfo.insert("time",time);
    //qDebug() << deviceinfo;
    QJson::Serializer serializer;
    bool ok;
    QByteArray data = serializer.serialize(deviceinfo,&ok);
    if (ok)
        return createCommandGeneral(supported_command[Login],data);
    return "";
}

QString CommandFactory::createCommandGeneral(QString command, QString data)
{
    return Command(command,data).toString();
}
