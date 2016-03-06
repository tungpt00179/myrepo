#ifndef RESPONSE_H
#define RESPONSE_H
#include <QFileInfo>
#include <QObject>
#include "../common.h"


class BusResponseBase:public QObject
{
    Q_OBJECT
    Q_ENUMS(SupportedCommand)

    Q_PROPERTY(SupportedCommand Command READ Command WRITE setCommand)
    Q_PROPERTY(int ResponseCode READ ResponseCode WRITE setResponseCode)
    Q_PROPERTY(QString Description READ Description WRITE setDescription)
    SupportedCommand m_command;

    int m_ResponseCode;

    QString m_Description;

public:

    SupportedCommand Command() const
    {
        return m_command;
    }
    int ResponseCode() const
    {
        return m_ResponseCode;
    }

    QString Description() const
    {
        return m_Description;
    }

public slots:
    void setCommand(SupportedCommand arg)
    {
        m_command = arg;
    }
    void setResponseCode(int arg)
    {
        m_ResponseCode = arg;
    }
    void setDescription(QString arg)
    {
        m_Description = arg;
    }
};

class Payload
{

public:
    int bus_number;
    QString from;
    QString to;
    int distance;
};

class BusResponseDistance :public QObject
{
    Q_OBJECT
    Q_ENUMS(SupportedCommand)

    Q_PROPERTY(SupportedCommand Command READ Command WRITE setCommand)
    Q_PROPERTY(long Time READ Time WRITE setTime)
    Q_PROPERTY(QList<Payload> Payloads READ Payloads)
    SupportedCommand m_Command;

    long m_Time;

QList<Payload> m_Payloads;

public:

    void addPayload(Payload p)
    {
        m_Payloads.append(p);
    }

SupportedCommand Command() const
{
    return m_Command;
}
long Time() const
{
    return m_Time;
}

QList<Payload> Payloads() const
{
    return m_Payloads;
}

public slots:
void setCommand(SupportedCommand arg)
{
    m_Command = arg;
}
void setTime(long arg)
{
    m_Time = arg;
}
};


class ResponseBase :public QObject
{
    Q_OBJECT
    Q_ENUMS(SupportedCommand)

    Q_PROPERTY(SupportedCommand command READ command WRITE command)
    Q_PROPERTY(int Error READ Error WRITE setError)
public:

    SupportedCommand command(){return m_command;}
    int Error() const
    {
        return m_Error;
    }

public slots:
    void command(SupportedCommand arg)
    {
        m_command = arg;
    }

    void setError(int arg)
    {
        m_Error = arg;
    }

private:
    SupportedCommand m_command;

    int m_Error;
};

class ResponseLogin :public ResponseBase
{
    Q_OBJECT
    Q_PROPERTY(QString DriverName READ DriverName WRITE setDriverName)
    Q_PROPERTY(int DriverID READ DriverID WRITE setDriverID)
    Q_PROPERTY(uint DriverState READ DriverState WRITE setDriverState)
    Q_PROPERTY(QString Phone READ Phone WRITE setPhone)
    Q_PROPERTY(QString Avatar READ Avatar WRITE setAvatar)
    Q_PROPERTY(int Rate READ Rate WRITE setRate)
    Q_PROPERTY(QString Account READ Account WRITE setAccount)
    Q_PROPERTY(QString PersonalID READ PersonalID WRITE setPersonalID)
    Q_PROPERTY(QString Email READ Email WRITE setEmail)
    Q_PROPERTY(QString PIDProvince READ PIDProvince WRITE setPIDProvince)
    Q_PROPERTY(QString LicenseNumber READ LicenseNumber WRITE setLicenseNumber)
    Q_PROPERTY(QString VehiclePlate READ VehiclePlate WRITE setVehiclePlate)
    Q_PROPERTY(QString VehicleModel READ VehicleModel WRITE setVehicleModel)
    Q_PROPERTY(int Seat READ Seat WRITE setSeat)
    Q_PROPERTY(bool Airport READ Airport WRITE setAirport)
    Q_PROPERTY(QString Password READ Password WRITE setPassword)
    Q_PROPERTY(QString Token READ Token WRITE setToken)

    QString m_DriverName;

    QString m_VehiclePlate;

    int m_DriverID;

    uint m_DriverState;

    QString m_Phone;

    QString m_Avatar;

    int m_Rate;

    QString m_Account;

    QString m_PersonalID;

    QString m_Email;

    QString m_PIDProvince;

    QString m_LicenseNumber;

    QString m_VehicleModel;

    int m_Seat;

    bool m_Airport;

    QString m_Password;

    QString m_Token;

public :
    ResponseLogin(){command(Login);}

    QString DriverName() const
    {
        return m_DriverName;
    }
    QString Phone() const
    {
        return m_Phone;
    }
    int DriverID() const
    {
        return m_DriverID;
    }
    uint DriverState() const
    {
        return m_DriverState;
    }
    QString Avatar() const
    {
        return m_Avatar;
    }
    int Rate() const
    {
        return m_Rate;
    }
    QString Account() const
    {
        return m_Account;
    }
    QString PersonalID() const
    {
        return m_PersonalID;
    }
    QString Email() const
    {
        return m_Email;
    }
    QString PIDProvince() const
    {
        return m_PIDProvince;
    }
    QString LicenseNumber() const
    {
        return m_LicenseNumber;
    }
    QString VehiclePlate() const
    {
        return m_VehiclePlate;
    }
    QString VehicleModel() const
    {
        return m_VehicleModel;
    }
    int Seat() const
    {
        return m_Seat;
    }
    bool Airport() const
    {
        return m_Airport;
    }
    QString Password() const
    {
        return m_Password;
    }
    QString Token() const
    {
        return m_Token;
    }

public slots:
    void setPassword(QString arg)
    {
        m_Password = arg;
    }
    void setToken(QString arg)
    {
        m_Token = arg;
    }
    void setDriverName(QString arg)
    {
        m_DriverName = arg;
    }
    void setDriverID(int arg)
    {
        m_DriverID = arg;
    }
    void setDriverState(uint arg)
    {
        m_DriverState = arg;
    }
    void setPhone(QString arg)
    {
        m_Phone = arg;
    }
    void setAvatar(QString arg)
    {
        m_Avatar = arg;
    }
    void setRate(int arg)
    {
        m_Rate = arg;
    }
    void setAccount(QString arg)
    {
        m_Account = arg;
    }
    void setPersonalID(QString arg)
    {
        m_PersonalID = arg;
    }
    void setEmail(QString arg)
    {
        m_Email = arg;
    }
    void setPIDProvince(QString arg)
    {
        m_PIDProvince = arg;
    }
    void setLicenseNumber(QString arg)
    {
        m_LicenseNumber = arg;
    }
    void setVehiclePlate(QString arg)
    {
        m_VehiclePlate = arg;
    }
    void setVehicleModel(QString arg)
    {
        m_VehicleModel = arg;
    }
    void setSeat(int arg)
    {
        m_Seat = arg;
    }
    void setAirport(bool arg)
    {
        m_Airport = arg;
    }
};

class ResponseUpdateDatabase
{
    quint64 m_ID;

    int m_Error;

public:

    quint64 ID() const
    {
        return m_ID;
    }

    int Error() const
    {
        return m_Error;
    }

public:

    void setID(quint64 arg)
    {
        m_ID = arg;
    }
    void setError(int arg)
    {
        m_Error = arg;
    }
};

#endif // RESPONSE_H
