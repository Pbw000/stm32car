#include "bluetooth_conn.h"
#include "ui_bluetooth_conn.h"
#include<QtBluetooth/qtbluetoothglobal.h>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QLabel>
#include<QPushButton>
#include<QFrame>
#include<QMessageBox>
#include<QListWidgetItem>
#include<QHBoxLayout>
#include<QTimer>
#include<QBluetoothServer>
#include <QBluetoothUuid>
#include<QBluetoothAddress>
#include<QBluetoothLocalDevice>
#include<QBluetoothSocket>
#include<QPointer>
#include <QBluetoothDeviceInfo>
#include"mainwindow.h"

Bluetooth_conn::Bluetooth_conn(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Bluetooth_conn) {
	ui->setupUi(this);


	discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
	connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Bluetooth_conn::additem);
	discoveryAgent->start();

}
void Bluetooth_conn::additem(const QBluetoothDeviceInfo& device) {
	QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
	QWidget* f = new QWidget(ui->listWidget);
	QHBoxLayout* layout = new QHBoxLayout();
	QLabel* l = new QLabel(device.name(), f);
	QPointer<QPushButton> btn = new QPushButton("连接", f);
	item->setSizeHint(QSize(0, 60));
	btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	btn->setProperty("deviceAddress", device.address().toString());
	l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	f->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	f->setMaximumSize(QSize(100000, 60));
	f->setMinimumSize(QSize(0, 60));
	layout->addWidget(l);
	layout->addWidget(btn);
	f->setLayout(layout);
	ui->listWidget->setItemWidget(item, f);
	connect(btn, &QPushButton::clicked, [btn, this, device]() {
        make_connection(btn, device.name(),device.address().toString());
	});
}



void Bluetooth_conn::make_connection(QPointer<QPushButton> btn,const QString& name,const QString& addr) {
	QMessageBox msgbox(QMessageBox::Question, "信息", "连接到" + btn->property("deviceAddress").toString(), QMessageBox::Yes | QMessageBox::Cancel, this);
	int ret = msgbox.exec();
	if (ret == QMessageBox::Cancel) {
		return;
	}

	btn->setText("正在连接");
	btn->setEnabled(false);
	QBluetoothSocket *socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
	QBluetoothAddress address(btn->property("deviceAddress").toString());
	QTimer* timer = new QTimer(this);
	timer->setInterval(10000);
	timer->setSingleShot(true);
	timer->start();
	connect(timer, &QTimer::timeout, [this, address, btn, socket, timer]() {
		delete timer;
		socket->abort();
		delete socket;
		QMessageBox msgbox(QMessageBox::Warning, "错误", address.toString() + "连接超时", QMessageBox::Ok, this);
		msgbox.exec();
		if (!btn.isNull()) {
			btn->setText("连接");
			btn->setEnabled(true);
		}
	});

	socket->connectToService(address, QBluetoothUuid(QString("00001101-0000-1000-8000-00805F9B34FB"))); // 使用串口服务UUID
    connect(socket, &QBluetoothSocket::connected, [btn, timer, socket, this,name,addr]() {
		timer->stop();
		delete timer;
		QMessageBox msgbox(QMessageBox::Information, "信息", "连接成功", QMessageBox::Ok, this);
		msgbox.exec();
		if (!btn.isNull()) {
			btn->setText("已连接");
		}
        emit connected(socket, name,addr);
	});
}

Bluetooth_conn::~Bluetooth_conn() {
	delete ui;
}

void Bluetooth_conn::on_scan_btn_clicked() {
	discoveryAgent->stop();
	ui->listWidget->clear();
	discoveryAgent->start();
}

