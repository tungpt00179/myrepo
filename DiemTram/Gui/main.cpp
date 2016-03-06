#include "driverform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // create empty update file
    QFile file("update.txt");
    if (file.open(QIODevice::WriteOnly))
        file.close();
    //qDebug() << QString::number((quint64)-1);
    DriverForm w;

#ifndef RPI
    w.show();
//    w.showMinimized();
#else
    w.showFullScreen();
#endif
    return a.exec();
}
