#ifndef DONGHO_H
#define DONGHO_H

#include <QSerialPort>
#include <QObject>
#include <QTimer>
#include <QDataStream>
#include <QThread>
#include "hwutils.h"

#define LOG qDebug() << QTime::currentTime().toString() << __FUNCTION__

class BanTinThuong
{
public:
    char Ten[3];
    quint64 ID;
    quint8 Vantoc;
    char ThoiGianXuongXe[5];
    quint8 TrangThai;
    quint16 KmRong;
    char ThoiGianLenXe[5];
    quint8 TrangThaiHongNgoai;
    char KmCoKhach[3];
    quint16 ThoiGianCho;
    quint16 IDCuocKhach;
    quint16 SoCa;
    char Tien[3];
    char KmTichLuy[3];
    quint8 Checksum;

public:
    operator QString()
    {
        return QString("C%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14")
                .arg(Ten[2])
                .arg(QString::number(Vantoc))
                .arg(bytes_to_date(ThoiGianXuongXe))
                .arg(QString::number(TrangThai))
                .arg(QString::number(KmRong))
                .arg(bytes_to_date(ThoiGianLenXe))
                .arg(QString::number(TrangThaiHongNgoai))
                .arg(char3_to_int(KmCoKhach))
                .arg(QString::number(ThoiGianCho))
                .arg(QString::number(IDCuocKhach))
                .arg(QString::number(SoCa))
                .arg(char3_to_int(Tien))
                .arg(char3_to_int(KmTichLuy))
                     .arg(QDateTime::currentDateTimeUtc().toTime_t());
    }
} ;

QDataStream& operator>> (QDataStream& d_stream, BanTinThuong& record);

class BanTinTongTichLuy
{
public:
    quint32 TongTien;
    quint32 KmCoKhach;
    quint32 KmRong;
    quint16 TongCuocKhach;
    quint32 VuotQuaTocDo;
    quint16 KichXung;
    quint16 ChayDa;
    quint16 MatNguon;
    quint32 ThoiGianCho;
    quint32 ThoiGianChoFree;
    quint16 SoXoaCa;
    quint32 SoBuocNhayTruocGiamGia;
    quint32 SoBuocNhayGiamGia;
    quint32 SoBuocNhayTruocGiamGiaDem;
    quint32 SoBuocNhayGiamGiaDem;
    quint16 SoCuocKhachDem;
    quint8 Checksum;

public:
    operator QString()
    {
        return QString("C7 %1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17")

                .arg(QString::number(TongTien))
                .arg(QString::number(KmCoKhach))
                .arg(QString::number(KmRong))
                .arg(QString::number(TongCuocKhach))
                .arg(QString::number(VuotQuaTocDo))
                .arg(QString::number(KichXung))
                .arg(QString::number(ChayDa))
                .arg(QString::number(MatNguon))
                .arg(QString::number(ThoiGianCho))
                .arg(QString::number(ThoiGianChoFree))
                .arg(QString::number(SoXoaCa))
                .arg(QString::number(SoBuocNhayTruocGiamGia))
                .arg(QString::number(SoBuocNhayGiamGia))
                .arg(QString::number(SoBuocNhayTruocGiamGiaDem))
                .arg(QString::number(SoBuocNhayGiamGiaDem))
                .arg(QString::number(SoCuocKhachDem))
                .arg(QDateTime::currentDateTimeUtc().toTime_t());
    }
};
QDataStream &operator>> (QDataStream& d_stream, BanTinTongTichLuy& record);


class BanTinTongCa
{
public:
    quint32 TongTien;
    quint32 KmCoKhach;
    quint32 KmRong;
    quint16 TongCuocKhach;
    quint32 VuotQuaTocDo;
    quint16 KichXung;
    quint16 ChayDa;
    quint16 MatNguon;
    quint32 ThoiGianCho;
    quint32 ThoiGianChoFree;
    quint8 LyDo;
    quint32 SoBuocNhayTruocGiamGia;
    quint32 SoBuocNhayGiamGia;
    quint32 SoBuocNhayTruocGiamGiaDem;
    quint32 SoBuocNhayGiamGiaDem;
    quint16 SoCuocKhachDem;
    quint8 Checksum;

public:
    operator QString()
    {
        return QString("C8 %1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17")

                .arg(QString::number(TongTien))
                .arg(QString::number(KmCoKhach))
                .arg(QString::number(KmRong))
                .arg(QString::number(TongCuocKhach))
                .arg(QString::number(VuotQuaTocDo))
                .arg(QString::number(KichXung))
                .arg(QString::number(ChayDa))
                .arg(QString::number(MatNguon))
                .arg(QString::number(ThoiGianCho))
                .arg(QString::number(ThoiGianChoFree))
                .arg(QString::number(LyDo))
                .arg(QString::number(SoBuocNhayTruocGiamGia))
                .arg(QString::number(SoBuocNhayGiamGia))
                .arg(QString::number(SoBuocNhayTruocGiamGiaDem))
                .arg(QString::number(SoBuocNhayGiamGiaDem))
                .arg(QString::number(SoCuocKhachDem))
                .arg(QDateTime::currentDateTimeUtc().toTime_t());
    }
};

QDataStream &operator>> (QDataStream& d_stream, BanTinTongCa& record);

class BanTinCuocKhach
{
public:
     char ThoiGianLenXe[5];
     char ThoiGianXuongXe[5];
     quint16 KmRong;
     quint32 KmCoKhach;
     quint32 TongTien;
     quint16 ThoiGianCho;
     quint16 ThoiGianChoFree;
     quint16 SoCa;
     quint16 STTCuoc;
     quint8 CheckSum;

     operator QString()
     {
         return QString("CA %1 %2 %3 %4 %5 %6 %7 %8 %9 %10")
                 .arg(bytes_to_date(ThoiGianLenXe))
                 .arg(bytes_to_date(ThoiGianXuongXe))
                 .arg(QString::number(KmRong))
                 .arg(QString::number(KmCoKhach))
                 .arg(QString::number(TongTien))
                 .arg(QString::number(ThoiGianCho))
                 .arg(QString::number(ThoiGianChoFree))
                 .arg(QString::number(SoCa))
                 .arg(QString::number(STTCuoc))
                 .arg(QDateTime::currentDateTimeUtc().toTime_t());
     }
};
QDataStream &operator>> (QDataStream& d_stream, BanTinCuocKhach& record);

class DongHo: public QObject
{
    Q_OBJECT

public:
    explicit DongHo(QString path,QObject *parent = 0);

    ~DongHo();
    bool open();
    void close();

    void init();
    void reset();

    bool chot_co();

    bool dong_bo_thoi_gian();

    bool xac_nhan_C5(quint16 id);

    bool Disconnected();
public slots:
    void got_data();
private slots:
    void timer_timeout();
    void on_serial_error(QSerialPort::SerialPortError);
signals:
    void GotData(QString rec);
private:
    bool checksum(QByteArray);
    void process_record(QByteArray);
private:
    QSerialPort *port;
    QByteArray data;
    QTimer m_timer;
    bool hasData;
    bool isDisconnected;
    bool need_baa;
    bool m_head_1;
    bool m_head_2;
    BanTinThuong m_current_record;
    QString m_path;
};

#endif // DONGHO_H
