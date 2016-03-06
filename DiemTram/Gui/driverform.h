#ifndef DRIVERFORM_H
#define DRIVERFORM_H

#include <QDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItem>
#include <QStringListModel>
#include <QToolButton>
#include <QWidget>
#include "network/core_network.h"
//#define RPI


namespace Ui {
class DriverForm;
}

class DriverForm : public QWidget
{
    Q_OBJECT

public:
    explicit DriverForm(QWidget *parent = 0);
    ~DriverForm();
public slots:
    void on_network_StateChanged(CoreState state);
    void resetLayout();

private slots:
    void updateName(QString);
    void updatePhone(QString);
    void gotNewDistance(QStringList);

private:
    void hideLogin();
private:
    Ui::DriverForm *ui;
    CoreNetwork *network;
    QStringListModel *model;
    QString m_current_driver_name;
    QString m_current_driver_phone;

};

#endif // DRIVERFORM_H
