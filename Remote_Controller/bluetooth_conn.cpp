#include "bluetooth_conn.h"
#include "ui_bluetooth_conn.h"
#include<QtBluetooth/qtbluetoothglobal.h>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QLabel>
#include<QPushButton>
#include<QFrame>
#include<QListWidgetItem>
#include<QHBoxLayout>
#include<QBluetoothServer>
#include <QBluetoothUuid>
#include<QBluetoothAddress>
#include<QBluetoothLocalDevice>
#include<QBluetoothSocket>
Bluetooth_conn::Bluetooth_conn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bluetooth_conn)
{    ui->setupUi(this);
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,this,&Bluetooth_conn::additem);
    discoveryAgent->start();

}
void Bluetooth_conn::additem(const QBluetoothDeviceInfo& device){
    QListWidgetItem* item=new QListWidgetItem(ui->listWidget);
    QWidget* f=new QWidget(ui->listWidget);
    QHBoxLayout* layout=new QHBoxLayout();
    QLabel* l=new QLabel(device.name(),f);
    QPushButton* btn=new QPushButton("连接",f);
    item->setSizeHint(QSize(0,60));
    btn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
    btn->setProperty("deviceAddress", device.address().toString());
    l->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    f->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    f->setMaximumSize(QSize(100000,60));
     f->setMinimumSize(QSize(0,60));
    layout->addWidget(l);
    layout->addWidget(btn);
    f->setLayout(layout);
    ui->listWidget->setItemWidget(item,f);
    connect(btn,&QPushButton::clicked,this,&Bluetooth_conn::make_connection);
}



void Bluetooth_conn::make_connection(){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn) {
        QBluetoothSocket *socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        QBluetoothAddress address(btn->property("deviceAddress").toString());
        qDebug() << "Device:" <<btn->property("deviceAddress").toString();
        socket->connectToService(address, QBluetoothUuid(QString("00001101-0000-1000-8000-00805F9B34FB"))); // 使用串口服务UUID
        connect(socket, &QBluetoothSocket::connected, [socket,this](){this->connected_socket=socket;qDebug() << "连接成功"; });
        qDebug() << "Connecting to:" << address.toString();
    }
}
Bluetooth_conn::~Bluetooth_conn()
{
    delete ui;
}

void Bluetooth_conn::on_scan_btn_clicked()
{
    discoveryAgent->stop();
    ui->listWidget->clear();
    discoveryAgent->start();
}

