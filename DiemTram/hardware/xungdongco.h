#ifndef XUNGDONGCO_H
#define XUNGDONGCO_H
#include <QThread>
#include <QTimer>

class XungDongCo: public QThread
{
    Q_OBJECT
public:
    explicit XungDongCo(int xung = 0, QObject *parent = 0);
    ~XungDongCo();

    void resetCounter();
signals:
    void event_report(double distance,double velocty);
public slots:
    void timer_timeout();
protected:
    void run();
private:
    int m_velocty;
    int m_count;
    int m_vel_count;
    int he_so_xung;
    QTimer* timer ;
};

#endif // XUNGDONGCO_H
