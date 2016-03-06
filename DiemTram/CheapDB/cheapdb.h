#ifndef CHEAPDB_H
#define CHEAPDB_H

#include <QSqlDatabase>
/**
 * @brief The CheapDB class
 * sql create database:
 * sqlite> create table gps(id integer primary key autoincrement,driver_id int,
                            latitude real, longitude real, v_gps int, v_co int,
                            status int, KmTichLuy int, time timestamp DEFAULT CURRENT_TIMESTAMP,
                            sent_status int DEFAULT 0);
 * sqlite> create table dongho(id integer primary key autoincrement,phanloai text,
                               noidung text, time timestamp default CURRENT_TIMESTAMP,
                               sent_status int default 0);
 * sqlite> create table thongtinchung(phanloai text, noidung text,
                                      time timestamp default CURRENT_TIMESTAMP)
 * sqlite> insert into thongtinchung(phanloai,noidung) values('KmTichLuy',0);
 * sqlite> insert into thongtinchung(phanloai,noidung) values('GpsInterval',2);
 * sqlite> create table baocaovantoc(time timestamp default CURRENT_TIMESTAMP, dulieu text)
 * sqlite> create table baocaodungdo(id integer primary key autoincrement,
                                     phanloai text, tenlaixe text, giaypheplaixe text,
                                     time timestamp default CURRENT_TIMESTAMP,
                                     latitude real, longitude real);
*/
class CheapDB
{

public:

    CheapDB();
    CheapDB(QString name);
    ~CheapDB();
    qint64 addGpsEntry(int driver_id,double lat, double lon,
                       int v_gps, int v_co,
                       int status,quint64 kmTichLuy,
                       bool isSent = false);
    QString getDuLieuGps();
    bool modifyGps(int id, int sent_status);

    bool addBaoCaoVanToc(QString);
    bool addBaoCaoDungDo(QString,QString,QString,double, double);

    bool modifyKmTichLuy(double value);
    quint64 getKmTichLuy();

    int getGpsInterval();
    bool modifyGpsInterval(int value);


    qint64 addDuLieuDongHo(QString, QString );
    QString getDuLieuDongHo();
    bool modifyDuLieuDongHo(int id, int sent_status);


protected:
    bool openDb(const char* dbname);
    void closeDb();
    QSqlDatabase& getDb();
private:
    QSqlDatabase db;
};

#endif // CHEAPDB_H
