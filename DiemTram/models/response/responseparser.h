#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

//#include <QDebug>
#include "response.h"

class ResponseParser
{
public:
    ResponseParser();
    ~ResponseParser();

    static bool parse_common(QString ba, QString &command, QString &data);

    static bool parse_bus_common(QString ba, BusResponseBase &response);

    static bool parse_bus_distance(QString data, BusResponseDistance &bus_response);
};

#endif // RESPONSEPARSER_H
