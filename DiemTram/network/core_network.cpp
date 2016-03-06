#include "core_network.h"
#include <QStringList>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <QMetaType>
#include <QProcess>
#include <QApplication>
#include <QMessageBox>
#include <QFileSystemWatcher>
#ifdef RPI
#include <wiringPi.h>
#endif
CoreNetwork::CoreNetwork(QObject *parent) : QObject(parent)
  #ifdef CHEAPDB_H
  ,db(DB_PATH)
  #endif
  //,m_rfid_state(0)
  //  ,m_current_meter_velocty(0)
  //,m_phanloai(0)
  ,watcher(this)
  ,need_update(false)
{
    //m_km_tich_luy = db.getKmTichLuy();
    //    m_gps_interval = db.getGpsInterval();

    //    LOG << m_gps_interval;
    m_profile = new DriverProfile();
    if (m_profile->load())
        m_State = S_NeedLogin;
    else m_State = S_InvalidProfile;
    //qRegisterMetaType< QAbstractSocket::SocketError >();
    if (State() ==  S_NeedLogin)
        init_network();
    idx = 0;tmp1 = 0;
    //QTimer::singleShot(5000,this,SLOT( test_rfid()) );
    QStringList version_str = QString(APP_VERSION).split('.');

    if (version_str.length() == 3)
    {
        m_app_version = (version_str[0].toInt() << 16) // major
                + (version_str[1].toInt() << 8)  // miror
                + version_str[2].toInt();        // patch
    }else
        m_app_version = 0;

    LOG << "App version:" << m_app_version << APP_VERSION;

#ifdef RPI
    system("gpio export 42 in");
    system("gpio export 41 in");
    system("gpio export 39 in");
    wiringPiSetupSys();
#endif
}

CoreNetwork::~CoreNetwork()
{
    if (m_socket != NULL)
        m_socket->close();
    delete m_socket;
    LOG << "socket destroyed!";

    delete m_profile;
}

bool CoreNetwork::init_profile()
{
    return m_profile->load();
}

void CoreNetwork::init_network()
{
    // network
    LOG << "start";
    //if (m_socket == NULL)
        m_socket = new QTcpSocket(this);

    LOG << "create signal connection";
    connect( m_socket, SIGNAL(connected()),this, SLOT(on_connected()),Qt::DirectConnection );
    connect( m_socket, SIGNAL(disconnected()),this, SLOT(on_disconnected()),Qt::DirectConnection );
    connect( m_socket, SIGNAL(readyRead()),this, SLOT(on_readyRead()),Qt::QueuedConnection );
    connect( m_socket, SIGNAL(error(QAbstractSocket::SocketError)),this ,SLOT(on_socket_error(QAbstractSocket::SocketError)));

    QString mes = QString("Adapter connecting to: %1:%2")
            .arg( m_profile->ServerUrl())
            .arg( m_profile->ServerPort());
    LOG << mes;
    m_socket->connectToHost(m_profile->ServerUrl(), m_profile->ServerPort());
    LOG << "a";
    if(m_socket->waitForConnected(3000)) {
        mes += " OK";
        LOG << "b";
        m_ready = true;

        setState(S_NeedLogin);
        //if (!loginToken())
        loginNew();
    }
    else
    {
        LOG << "c";
        mes += "Failed!";
    }
    LOG << mes;
}

DriverProfile* CoreNetwork::Profile()
{
    return m_profile;
}

CoreState CoreNetwork::State() const
{
    return m_State;
}

void CoreNetwork::on_connected()
{
    LOG << "connected!";
    m_ready = true;
}

void CoreNetwork::on_disconnected()
{
    LOG << "disconnected!";
    m_ready = false;
}

void CoreNetwork::on_readyRead()
{

    while(m_socket->canReadLine())
    {
        QByteArray ba = m_socket->readLine();
        // print data
        LOG << State() << ba;
        QString command, data;
        if (!ResponseParser::parse_common(ba, command,data)) return;
        //LOG << State();
        // if command is ack, do nothing
        //LOG << State() << ba;

        // in wating login response state
        if (State() == S_Waiting
                && command == supported_command[Login])
        {
            //LOG << "parse login new";

            BusResponseBase response;
            if (ResponseParser::parse_bus_common(data, response)
                    && response.ResponseCode() == 0)
                setState(S_Ready);
            else
                setState(S_NeedLogin);
        }

        else if (State() >= S_Ready &&
                 command == supported_command[TimeDistance])
        {
            BusResponseDistance ret;
            ResponseParser::parse_bus_distance(data,ret);

            QStringList list;

            foreach (Payload p, ret.Payloads()) {
                QString str;
                str = QString("Xe: %1\nTừ: %2\nĐến: %3\nKhoảng cách: %4Km")
                        .arg(p.bus_number).arg(p.from).arg( p.to).arg( p.distance/1000);
                list<< str;
            }

            emit NewDistance(list);
        }
    }
}

void CoreNetwork::on_socket_error(QAbstractSocket::SocketError error)
{
    //    m_running = false;
    //    cond.wakeAll();
    m_ready = false;
    LOG << m_socket->errorString() << error;
}

void CoreNetwork::setState(CoreState arg)
{
    if (m_State == arg)
        return;
    LOG << arg;
    m_State = arg;
    emit StateChanged(arg);
}

bool CoreNetwork::loginNew()
{
    LOG << State();
    if (State() > S_NeedLogin) return false;
    QString command = CommandFactory::createLoginCmd(
                m_profile->DeviceImei(), m_profile->SimImei(),
                QDateTime::currentDateTimeUtc().toTime_t());

    LOG << command;
    m_socket->write(command.toStdString().c_str());

    bool ret =  m_socket->waitForBytesWritten();
    if (ret)
    {
        setState(S_Waiting);
    }
    else
    {
        if (m_socket->state() == QTcpSocket::ConnectedState)
            setState(S_Ready);
        else
            setState(S_NetError);
    }
    return ret;
}




