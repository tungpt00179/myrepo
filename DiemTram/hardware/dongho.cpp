#include "dongho.h"

DongHo::DongHo(QString path,QObject *parent)
    : QObject(parent)
    ,m_timer(this)
    ,hasData(false)
    ,isDisconnected(true)
    ,need_baa(false)
{
    m_head_1 = false;
    m_head_2 = false;

    m_timer.setInterval(10000);
    m_timer.setSingleShot(true);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(timer_timeout()));

    m_path = path;
    if (m_path.length() > 0)
    {
        init();
        //open();
    }
    else
        LOG << "DongHo" << "invalid path";
}

DongHo::~DongHo()
{
    close();
    delete port;
}


void DongHo::init()
{
    //LOG;
    port = new QSerialPort(this);
    connect(port, SIGNAL(readyRead()),
            this, SLOT(got_data()));
    connect(port,SIGNAL(error(QSerialPort::SerialPortError)),
            this,SLOT(on_serial_error(QSerialPort::SerialPortError)));
    port->setPortName(m_path);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
}


// opens the serial port specified py path
bool DongHo::open() {
    //LOG << m_path;
    m_timer.start();
    if (!port->open(QIODevice::ReadWrite))
    {
        LOG << "DongHo" << port->errorString();
        return false;
    }
    isDisconnected = false;
    return true;
}

// close the serial port
void DongHo::close() {
    LOG << "DongHo";
    if (port->isOpen())
        port->close();
}

bool DongHo::chot_co()
{
    if (port->isOpen())
    {
        port->write("BA7#");
        return port->waitForBytesWritten(1000);
    }
    return false;
}

bool DongHo::dong_bo_thoi_gian()
{
    LOG<< "DongHo";
    if (port->isOpen())
    {
        QByteArray cmd;
        cmd.append("BA,3,1,");
        cmd.append(QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ssddd"));
        port->write(cmd);
        return port->waitForBytesWritten(1000);
    }
    return false;
}

bool DongHo::xac_nhan_C5(quint16 id)
{
    if (port->isOpen())
    {
        QByteArray cmd;
        cmd.append(QString("BA5,%1,OK").arg(id));
        LOG<< cmd;
        port->write(cmd);
        return port->waitForBytesWritten(1000);
    }
    return false;
}

bool DongHo::Disconnected()
{
    return isDisconnected || !hasData;
}
void DongHo::reset()
{
    LOG;
    m_current_record.Checksum = 0;
    isDisconnected = true;
    close();
    open();
}

void DongHo::got_data()
{
    int len = port->bytesAvailable();

    QByteArray tmp;

    if (len > 0)
    {
        tmp = port->read(len);
        //LOG << len  << tmp.toHex();


        //return;
        Q_FOREACH(char c,tmp)
        {
            //LOG << count << (int)c
            //    << m_head_1 <<m_head_2;
            if (!m_head_1 && c == 'B')
                m_head_1 = true;
            else if (m_head_1
                && (c == 'A' || c == 'a'))
                m_head_2 = true;
            else if (m_head_1
                && c != 'A' && c != 'a')
                    m_head_1 = false;
            data.append(c);

            if (m_head_1 && m_head_2 )
            {
                if (data.length() > 2)
                    process_record(data.left(data.length()-2));
                data.clear();
                data.append("BA");
                m_head_1 = false;
                m_head_2 = false;
            }

        }
        return;
    }
}

void DongHo::timer_timeout()
{
    if (isDisconnected)
        reset();
    else
    {
        //LOG << hasData;
        if (hasData)
        {
            hasData = false;
        }

        m_timer.start();
    }
}

void DongHo::on_serial_error(QSerialPort::SerialPortError error)
{
    LOG << "dongho" << error << port->errorString();
    if (error != QSerialPort::NoError
            //            && error != QSerialPort::ResourceError
            && error != QSerialPort::UnknownError)
    isDisconnected = true;
}

bool DongHo::checksum(QByteArray data)
{
    int val = 0;
    for (int i = 0; i < data.length()-1;
         i++)
    {
        val += data.at(i);
    }
    val &=0xff;
    return (val == data.at(data.length()-1));
    //LOG << ret;
    //return ret;

    //return false;
}

void DongHo::process_record(QByteArray data)
{
    if (!checksum(data)) return;
    QDataStream d_stream(data);
    //LOG << data.length() << data[2];

    if (data[0] == 'B' && data[1] == 'A'
            && data[2] > '0' && data[2] < '6'
            && data.length() == 34)
    {

        //LOG << data[2] << m_current_record.Ten[2];
        hasData = ((quint8)data[33]
                != m_current_record.Checksum)
                || (data[2]
                    != m_current_record.Ten[2])
                ?true:false;
        d_stream >> m_current_record;
        if (data[2] == '5')
        {
            xac_nhan_C5(m_current_record.IDCuocKhach);
            LOG << data.length() << data.toHex();
        }
        if (hasData)
        {
            emit GotData(m_current_record);
        }
    }

    else if (data.startsWith("BA7")
             && data.length() == 56)
    {
        hasData = true;//(quint8)data[55] != m_current_record.Checksum?true:false;
        if (hasData)
        {
            BanTinTongTichLuy bantin;
            d_stream >> bantin;

            emit GotData(bantin);
        }
    }
    else if (data.startsWith("BA8")
             && data.length() == 55)
    {
        need_baa = (quint8)data[35] == 1?true:false;
        hasData = true;//(quint8)data[54] != m_current_record.Checksum?true:false;
        if (hasData)
        {
            BanTinTongCa bantin;
            d_stream >> bantin;
            if (port->isOpen())
            {
                QByteArray cmd;
                cmd.append("BA8,OK");
                LOG<< cmd;
                port->write(cmd);
                port->waitForBytesWritten(1000);
            }
            emit GotData(bantin);
        }
    }
    else if (need_baa && data.startsWith("BAA")
             && data.length() == 32)
    {
        //LOG << "goi tin tong ca" << data.length();
        QDataStream d_stream(data);
        BanTinCuocKhach bantin;
        d_stream >> bantin;
        emit GotData(bantin);
    }
    hasData = true;
}


QDataStream &operator>>(QDataStream &d_stream, BanTinThuong &record)
{
    d_stream.readRawData(record.Ten,3);

    d_stream >> record.Vantoc;

    d_stream.readRawData(record.ThoiGianXuongXe,5);

    d_stream >> record.TrangThai;
    d_stream >> record.KmRong;
    d_stream.readRawData(record.ThoiGianLenXe,5);

    d_stream >> record.TrangThaiHongNgoai;
    d_stream.readRawData(record.KmCoKhach,3);
    d_stream >> record.ThoiGianCho;
    d_stream >> record.IDCuocKhach;
    d_stream >> record.SoCa;
    d_stream.readRawData(record.Tien,3);
    d_stream.readRawData(record.KmTichLuy,3);
    d_stream >> record.Checksum;

    return d_stream;
}


QDataStream &operator>>(QDataStream &d_stream, BanTinTongTichLuy &record)
{
    d_stream.skipRawData(3);
    d_stream >> record.TongTien >> record.KmCoKhach >> record.KmRong >> record.TongCuocKhach
             >> record.VuotQuaTocDo >> record.KichXung >> record.ChayDa >> record.MatNguon
             >> record.ThoiGianCho >> record.ThoiGianChoFree >> record.SoXoaCa
             >> record.SoBuocNhayTruocGiamGia >> record.SoBuocNhayTruocGiamGiaDem
             >> record.SoBuocNhayGiamGia >> record.SoBuocNhayGiamGiaDem
             >> record.SoCuocKhachDem >> record.Checksum;

    return d_stream;
}

QDataStream &operator>>(QDataStream &d_stream, BanTinTongCa &record)
{
    d_stream.skipRawData(3);
    d_stream >> record.TongTien >> record.KmCoKhach >> record.KmRong >> record.TongCuocKhach
             >> record.VuotQuaTocDo >> record.KichXung >> record.ChayDa >> record.MatNguon
             >> record.ThoiGianCho >> record.ThoiGianChoFree >> record.LyDo
             >> record.SoBuocNhayTruocGiamGia >> record.SoBuocNhayTruocGiamGiaDem
             >> record.SoBuocNhayGiamGia >> record.SoBuocNhayGiamGiaDem
             >> record.SoCuocKhachDem >> record.Checksum;

    return d_stream;
}

QDataStream &operator>>(QDataStream &d_stream, BanTinCuocKhach &record)
{
    d_stream.skipRawData(3);
    d_stream.readRawData(record.ThoiGianLenXe,5);
    d_stream.readRawData(record.ThoiGianXuongXe,5);
    d_stream >> record.KmRong >> record.KmCoKhach >> record.TongTien
             >> record.ThoiGianCho >> record.ThoiGianChoFree >> record.SoCa
             >> record.STTCuoc >> record.CheckSum;
    return d_stream;
}
