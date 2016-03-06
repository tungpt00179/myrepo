#include "xungdongco.h"
#include "wiringPi.h"
#include <QTime>
#include "log/log.h"
XungDongCo::XungDongCo(int xung,QObject *parent) :
    QThread(parent),m_count(0),m_velocty(0),m_vel_count(0),he_so_xung(xung)
{
    if (he_so_xung != 0)
    {
        timer = new QTimer();
        timer->setInterval(100);
        timer->setSingleShot(false);
        connect(timer,SIGNAL(timeout()),this,SLOT(timer_timeout()));
    }else
    {
        LOG << "Sai he so xung(0)";
    }
}

XungDongCo::~XungDongCo()
{
    delete timer;
}

void XungDongCo::timer_timeout()
{
    if (he_so_xung > 0)
    {
        m_vel_count++;
        double distance = 0;
        distance = m_count * 1000 / he_so_xung;
        if (m_vel_count >= 10)
        {
            m_velocty = m_velocty * 3600 / he_so_xung;
            m_vel_count = 0;
            emit event_report(distance,m_velocty);
            m_velocty = 0;
        }//else
        // emit event_report(distance,-1);
    }

}
void XungDongCo::resetCounter()
{
    m_count = 0;
    m_velocty = 0;
    m_vel_count = 0;
}

void XungDongCo::run(){
    system("gpio edge 34 falling");
    wiringPiSetupSys();
    piHiPri(99);
    timer->start();
    Q_FOREVER{
        if (waitForInterrupt(34,-1) > 0)
        {
            m_count ++;
            m_velocty ++;
        }
    }
}
