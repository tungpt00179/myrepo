#include "responseparser.h"
#include <qjson/parser.h>

#include <QDebug>
#include <QTime>
#define LOG qDebug() << QTime::currentTime().toString() << __FUNCTION__

bool ResponseParser::parse_common(QString ba, QString &command, QString &data)
{
    int index1 = ba.indexOf(PKG_SEPERATOR, 0);

    if (index1 != -1 )
    {
        command = ba.left(index1);
        data = ba.mid(index1+1).simplified();
        //LOG << command << data;
        return true;
    }
    else
        return false;
}

bool ResponseParser::parse_bus_common(QString ba, BusResponseBase &response)
{
    QJson::Parser parser;
    bool ok;
    //LOG << ba;
    // json is a QString containing the data to convert
    QVariantMap mapObj = parser.parse(ba.toUtf8(), &ok).toMap();
    if (ok)
    {
        // dump map object
        LOG << mapObj;
        response.setCommand(
                    supported_command.key(mapObj["CommandName"].toString()));
        response.setResponseCode(mapObj["code"].toInt(&ok));

    }
    return ok;
}

bool ResponseParser::parse_bus_distance(QString data, BusResponseDistance &bus_response)
{
    QJson::Parser parser;
    bool ok;
    // json is a QString containing the data to convert
    QVariantMap mapObj = parser.parse(data.toUtf8(), &ok).toMap();
    if (ok)
    {
        // dump map object
        //LOG << mapObj;
        bus_response.setCommand(supported_command.key(mapObj["CommandName"].toString()));
        bus_response.setTime(mapObj["time"].toLongLong(&ok));
        if (ok)
        {
            foreach(QVariant plugin, mapObj["payloads"].toList())
            {
                Payload p;
                p.bus_number = plugin.toMap()["bus_number"].toInt(&ok);
                p.from = plugin.toMap()["from"].toString();
                p.to = plugin.toMap()["to"].toString();
                p.distance = plugin.toMap()["distance"].toInt(&ok);
//                LOG << p.bus_number << " - "
//                    << p.from << " - "
//                    << p.to << " - "
//                    << p.distance ;
                if (ok)
                {
                    bus_response.addPayload(p);
                }
            }
            //bus_response.setDescription(mapObj["description"].toString());
            ok = true;
        }
    }
    return ok;
}
