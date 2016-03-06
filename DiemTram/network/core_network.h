#ifndef CORENETWORK_H
#define CORENETWORK_H

#include <QThread>
#include <QStack>
#include <QMutex>
#include <QWaitCondition>
#include <QDateTime>
#include <QTcpSocket>

#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QFileSystemWatcher>
#define LOG qDebug() << QTime::currentTime().toString() << __FUNCTION__
#include "models/models.h"

#include "CheapDB/cheapdb.h"
#define DB_PATH "cheap.db"

//#define RPI

enum CoreState
{
    S_NoProfile,
    S_InvalidProfile,
    S_NeedLogin,
    S_Waiting,
    S_NetError,
    S_Ready
};

class CoreNetwork : public QObject
{
    Q_OBJECT
    Q_ENUMS(CoreState)
    Q_PROPERTY(CoreState State READ State WRITE setState)

public slots:
    void on_connected();
    void on_disconnected();
    void on_readyRead();
    void on_socket_error(QAbstractSocket::SocketError);
    void setState(CoreState arg);

    bool loginNew();

public:
    CoreNetwork(QObject *parent = 0);
    ~CoreNetwork();

signals:

    void StateChanged(CoreState arg);

    void UserNameChanged(QString);

    void UserPhoneChanged(QString);

    void NewDistance(QStringList);

private:
    QTcpSocket *m_socket;
    DriverProfile *m_profile;
    bool m_ready;

    CoreState m_State;

public:
    bool init_profile();
    void init_network();

    DriverProfile* Profile();
    CoreState State() const;
private:
#ifdef CHEAPDB_H
    CheapDB db;
#endif

//    double m_current_latitude;
//    double m_current_longitude;
//    double m_current_gps_velocty;
//    double m_current_meter_velocty;
//    Location m_lenxe;
//    Location m_xuongxe;
    //double m_km_tich_luy;
    //quint8 m_phanloai;
//    quint32 m_gps_interval;
//    QString m_v_data;
    int idx;
    int tmp1;
    bool isStop;
    quint32 m_app_version;
    QFileSystemWatcher watcher;
    bool need_update;
};

#endif // CORENETWORK_H
