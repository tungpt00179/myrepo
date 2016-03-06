#include "cheapdb.h"
#include <QSqlQuery>
#include "utils/log/log.h"

CheapDB::CheapDB()
{

}

CheapDB::CheapDB(QString name)
{
    openDb(name.toStdString().c_str());
}

CheapDB::~CheapDB()
{
    closeDb();
}

qint64 CheapDB::addGpsEntry(int driver_id,double lat, double lon,
                            int v_gps, int v_co, int status,quint64 kmTichLuy, bool isSent)
{
    QSqlQuery query;

    if (query.exec(
            QString("insert into gps(driver_id, latitude, longitude, v_gps, v_co, status,KmTichLuy,sent_status) "
                    "values(%1, %2, %3, %4, %5, %6, %7, %8);").arg(driver_id)
            .arg(QString::number(lat, 'f', 10))
            .arg(QString::number(lon, 'f', 10))
            .arg(v_gps).arg(v_co)
            .arg(status).arg(kmTichLuy)
                .arg(isSent?"1":"0")))
    {
        //LOG << query.lastQuery();
        return query.lastInsertId().toInt();
    }
    else
    {
        LOG << query.lastQuery();
        return -1;
    }
}

qint64 CheapDB::addDuLieuDongHo(QString phanloai, QString noidung)
{
    QSqlQuery query;
    //LOG;
    if (query.exec(
                QString("insert into dongho(phanloai,noidung) "
                        "values(\"%1\",\"%2\");")
                .arg(phanloai).arg(noidung)))
    {
        return query.lastInsertId().toInt();
    }
    else
    {
        return -1;
    }
}

bool CheapDB::addBaoCaoVanToc(QString dulieu)
{
    QSqlQuery query;
    //LOG;
    return query.exec(QString("insert into baocaovantoc(dulieu) values(\"%1\");")
                      .arg(dulieu));
}

///
/// \brief CheapDB::addBaoCaoDungDo
/// \param action: MUST be "IN" or "OUT"
/// \param dulieu
/// \return
///
bool CheapDB::addBaoCaoDungDo(QString action,QString tenlaixe, QString giaypheplaixe,
                              double latitude, double longitude)
{
    if (action != "IN" && action != "OUT") return false;

    QSqlQuery query;
    //LOG;
    return query.exec(
    QString("insert into baocaodungdo(phanloai,tenlaixe,giaypheplaixe,latitude,longitude)"
                              " values(\"%1\",\"%2\",\"%3\",%4,%5);")
                .arg(action).arg(tenlaixe).arg(giaypheplaixe)
                .arg(QString::number(latitude, 'f', 10))
                .arg(QString::number(longitude, 'f', 10)));
}

QString CheapDB::getDuLieuGps()
{
    QSqlQuery query;
    //LOG;
    if (query.exec("select id,driver_id,latitude,longitude,v_gps,v_co,status,strftime('%s',time) from gps where sent_status = 0 order by time asc limit 1;"))
    {
        if( query.first())
            return QString( "GPS %1 %2 %3 %4 %5 %6 %7 %8\r\n")
                    .arg( query.value(0).toString() )
                    .arg( query.value(1).toString() )
                    .arg( query.value(2).toString() )
                    .arg( query.value(3).toString() )
                    .arg( query.value(4).toString() )
                    .arg( query.value(5).toString() )
                    .arg( query.value(6).toString() )
                    .arg( query.value(7).toString() );

    }
    return "";
}

quint64 CheapDB::getKmTichLuy()
{
    QSqlQuery query;
    //LOG;
    if (query.exec("select noidung from thongtinchung where phanloai='KmTichLuy'"))
    {
        if( query.first())
            return query.value(0).toInt();
    }
    return 0;
}

int CheapDB::getGpsInterval()
{
    QSqlQuery query;
    //LOG;
    if (query.exec("select noidung from thongtinchung where phanloai='GpsInterval'"))
    {
        if( query.first())
            return query.value(0).toInt();
    }
    return 0;
}

QString CheapDB::getDuLieuDongHo()
{
    QSqlQuery query;

    if (query.exec("select id, phanloai, noidung from dongho where sent_status = 0 order by time asc limit 1;"))
    {
        if (query.next())
            return QString( "%1 %2 %3\r\n" ).arg( query.value(1).toString() )
                    .arg( query.value(0).toString() )
                    .arg( query.value(2).toString() );
    }
    return "";

}

bool CheapDB::modifyGps(int id, int sent_status)
{
    QSqlQuery query;
    //LOG << id;
    if (query.exec(QString("update gps set sent_status = %1 where id = %2;").arg(sent_status).arg(id)))
    {
        return true;
    }
    LOG << id << "falsed";
    return false;
}

bool CheapDB::modifyDuLieuDongHo(int id, int sent_status)
{
    QSqlQuery query;
    //LOG << id;
    if (query.exec(QString("update dongho set sent_status = %1 where id = %2;").arg(sent_status).arg(id)))
    {
        return true;
    }
    LOG << id << "falsed";
    return false;
}

bool CheapDB::modifyKmTichLuy(double value)
{
    QSqlQuery query;
//    LOG << value;
    if (query.exec(
        QString("update thongtinchung set noidung = %1 where phanloai = 'KmTichLuy';")
                .arg(value)))
    {
        return true;
    }
    LOG << value << "falsed";
    return false;
}

bool CheapDB::modifyGpsInterval(int value)
{
    QSqlQuery query;
//    LOG << value;
    if (query.exec(
        QString("update thongtinchung set noidung = %1 where phanloai = 'GpsInterval';")
                .arg(value)))
    {
        return true;
    }
    LOG << value << "falsed";
    return false;
}

bool CheapDB::openDb(const char* dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if (!db.open()) {
        LOG << "Cannot open database";
        return false;
    }
    return true;
}

void CheapDB::closeDb()
{
    db.close();
}

QSqlDatabase& CheapDB::getDb()
{
    return db;
}
