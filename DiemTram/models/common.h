#ifndef COMMON_H
#define COMMON_H
#include <QDateTime>
#include <QString>
#include <QVariant>
#define PKG_SEPERATOR " "

#define PKG_START "_W_C_B_"
#define PKG_START_LEN 7
//#define PKG_SEPERATOR " "
#define PKG_SEPERATOR_LEN 1
#define PKG_END "_W_C_E_"
#define PKG_END_LEN 7

enum SupportedCommand
{
    Login = 0,
    TimeDistance
};

static QMap<SupportedCommand,QString> create_commands() {
    QMap<SupportedCommand,QString> commands;
    commands.insert(Login,"Login");

    commands.insert(TimeDistance, "TimeDistance");

    return commands;
}
static QMap<SupportedCommand,QString> supported_command = create_commands();

class Location
{

    QString m_name;
    double m_Longitude;
    double m_Latitude;

public:
    Location(QVariant data){
        setName(QString::fromUtf8(data.toMap()["Name"].toByteArray()));
        setLongitude(data.toMap()["Longtitude"].toDouble());
        setLatitude(data.toMap()["Latitude"].toDouble());
    }

    Location(double lon,double lat):m_name(""),m_Longitude(lon),m_Latitude(lat){}

    Location():m_name(""),m_Longitude(0),m_Latitude(0){}

    QString toString(){
        return "(" + m_name + ": " + QString::number(m_Latitude) + "," + QString::number(m_Longitude) + ")";
    }

    double Longitude() const
    {
        return m_Longitude;
    }
    double Latitude() const
    {
        return m_Latitude;
    }
    QString Name() const
    {
        return m_name;
    }

    void setName(QString arg)
    {
        m_name = arg;
    }
    void setLatitude(double arg)
    {
        m_Latitude = arg;
    }
    void setLongitude(double arg)
    {
        m_Longitude = arg;
    }
};

#endif // COMMON_H
