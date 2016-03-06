#include "driverprofile.h"
#include "utils/log/log.h"

DriverProfile::DriverProfile(QString s_url, uint s_port, uint d_id,
                             QString d_plate, QString d_os)
{
    m_ServerUrl = s_url;
    m_ServerPort = s_port;
    m_DeviceID = d_id;
    m_DevicePlate = d_plate;
    m_DeviceOSType = d_os;
}

DriverProfile::~DriverProfile()
{
    delete cfg;
}

QString DriverProfile::ServerUrl() const
{
    return m_ServerUrl;
}

uint DriverProfile::ServerPort() const
{
    return m_ServerPort;
}

uint DriverProfile::DeviceID() const
{
    return m_DeviceID;
}

QString DriverProfile::DevicePlate() const
{
    return m_DevicePlate;
}

QString DriverProfile::DeviceOSType() const
{
    return m_DeviceOSType;
}

quint32 DriverProfile::HeSoXung() const
{
    return m_HeSoXung;
}

QString DriverProfile::DeviceImei() const
{
    return m_DeviceImei;
}

QString DriverProfile::SimImei() const
{
    return m_SimImei;
}

void DriverProfile::setServerUrl(QString arg)
{
    m_ServerUrl = arg;
}

void DriverProfile::setServerPort(uint arg)
{
    m_ServerPort = arg;
}

void DriverProfile::setDeviceID(uint arg)
{
    m_DeviceID = arg;
}

void DriverProfile::setDevicePlate(QString arg)
{
    m_DevicePlate = arg;
}

void DriverProfile::setDeviceOSType(QString arg)
{
    m_DeviceOSType = arg;
}

void DriverProfile::setDeviceImei(QString arg)
{
    m_DeviceImei = arg;
}

void DriverProfile::setSimImei(QString arg)
{
    m_SimImei = arg;
}

bool DriverProfile::load()
{
    bool ret = false;
    cfg= new DeviceCfg( CONFIG_PATH );
    ret = cfg->load();
    if (!ret) return ret;
    QString s_url, d_plate, d_os;
    uint s_port, d_id;
    quint32 d_xung;
    // network profile
    s_url = cfg->getString("Network","ServerURL","");
    s_port = cfg->getInt("Network","ServerPort",0);
    if (s_url.length() == 0 && s_port == 0)
    {
        return false;
    }
    // device profile
    d_id = cfg->getInt("Device","DeviceId",0);
    d_plate = cfg->getString("Device","DevicePlate","");
    d_os = cfg->getString("Device","OSType","");
    d_xung = cfg->getInt("Device","HeSoXung",0);
    if (d_id == 0 && d_plate.length() == 0 && d_os.length() == 0)
        return false;

    m_ServerUrl = s_url;
    m_ServerPort = s_port;
    m_DeviceID = d_id;
    m_DevicePlate = d_plate;
    m_DeviceOSType = d_os;
    m_HeSoXung = d_xung;

    // driver profile
    setDeviceImei(cfg->getString("Serial","DeviceImei","000000000000000"));
    setSimImei(cfg->getString("Serial","SimImei","000000000000000"));

    print_settings();
    return true;
}

bool DriverProfile::save()
{
    return cfg->save();
}

void DriverProfile::print_settings()
{
    LOG << "* Current settings:";
    LOG << "* ServerURL : " << ServerUrl();
    LOG << "* ServerPort: " << ServerPort() << endl;

    LOG << "* Device ID   : " << DeviceID();
    LOG << "* Device Plate: " << DevicePlate();
    LOG << "* OSType      : " << DeviceOSType() << endl;
    LOG << "* HeSoXung    : " << HeSoXung() << endl;

    LOG << "* Driver Imei : " << DeviceImei();
    LOG << "* Sim    Imei : " << SimImei();
}

