#ifndef DRIVERPROFILE_H
#define DRIVERPROFILE_H
#include <QObject>
#include "utils/config/deviceconfig.h"

#define CONFIG_PATH "config/settings.ini"
#define DeviceCfg core::utils::config::DeviceCfg

class DriverProfile :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ServerUrl READ ServerUrl)
    Q_PROPERTY(uint ServerPort READ ServerPort)

    Q_PROPERTY(uint DeviceID READ DeviceID)
    Q_PROPERTY(QString DevicePlate READ DevicePlate)
    Q_PROPERTY(QString DeviceOSType READ DeviceOSType)
    Q_PROPERTY(quint32 HeSoXung READ HeSoXung)

    Q_PROPERTY(QString DeviceImei READ DeviceImei WRITE setDeviceImei)
    Q_PROPERTY(QString SimImei READ SimImei WRITE setSimImei)

public:
    DriverProfile(QString s_url="",uint s_port = 0, uint d_id = 0,
                  QString d_plate="", QString d_os = "");
    ~DriverProfile();

    QString ServerUrl() const;

    uint ServerPort() const;

    uint DeviceID() const;

    QString DevicePlate() const;

    QString DeviceOSType() const;

    quint32 HeSoXung() const;

    QString DeviceImei() const;

    QString SimImei() const;

public slots:
    void setServerUrl(QString arg);

    void setServerPort(uint arg);

    void setDeviceID(uint arg);

    void setDevicePlate(QString arg);

    void setDeviceOSType(QString arg);

    bool load();

    bool save();

    void print_settings();

    void setDeviceImei(QString arg);

    void setSimImei(QString arg);

private:
    DeviceCfg *cfg;

    QString m_ServerUrl;
    uint m_ServerPort;
    uint m_DeviceID;
    QString m_DevicePlate;
    QString m_DeviceOSType;
    quint32 m_HeSoXung;
    QString m_DeviceImei;
    QString m_SimImei;
};


#endif // DRIVERPROFILE_H
