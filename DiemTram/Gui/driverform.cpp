#include "driverform.h"
#include "ui_driverform.h"
#include "unistd.h"
#include <QStandardItem>

DriverForm::DriverForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DriverForm)
{
    ui->setupUi(this);
    ui->lbThongtinHang->setText(BRAND_NAME);
    ui->lbThongtinPhienban->setText(APP_VERSION);

    network = new CoreNetwork();
    connect(network, SIGNAL(StateChanged(CoreState)),
            this, SLOT(on_network_StateChanged(CoreState)));

    connect(network,SIGNAL(UserNameChanged(QString)),this,SLOT(updateName(QString)));

    connect(network,SIGNAL(UserPhoneChanged(QString)),this,SLOT(updatePhone(QString)));

    connect(network,SIGNAL(NewDistance(QStringList)),this,SLOT(gotNewDistance(QStringList)));
    //current_job.OrderId = 0;
    model = new QStringListModel();
    ui->listView->setModel(model);
}

DriverForm::~DriverForm()
{
    delete network;
    delete ui;
}

void DriverForm::resetLayout()
{
    ui->lbThongtinMang->setText(QString::fromUtf8("Đã kết nối tới máy chủ"));
}

void DriverForm::on_network_StateChanged(CoreState state)
{
    LOG << state;
    if (state == S_Ready)
        resetLayout();
}

void DriverForm::updateName(QString name)
{
    m_current_driver_name = name;
}

void DriverForm::updatePhone(QString phone)
{
    m_current_driver_phone = phone;
}

void DriverForm::gotNewDistance(QStringList list)
{
    LOG << list;
    model->setStringList(list);
    ui->listView->setModel(model);
}
