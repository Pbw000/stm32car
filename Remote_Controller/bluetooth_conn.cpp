#include "bluetooth_conn.h"
#include "ui_bluetooth_conn.h"
#include<QBluetoothDeviceDiscoveryAgent>
Bluetooth_conn::Bluetooth_conn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bluetooth_conn)
{QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            [](const QBluetoothDeviceInfo &device) {
                qDebug() << "Found device:" << device.name() << device.address();
            });
    discoveryAgent->start(); // 开始扫描
    ui->setupUi(this);
}

Bluetooth_conn::~Bluetooth_conn()
{
    delete ui;
}
