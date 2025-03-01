#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config_dialog.h"
#include"route.h"
#include"bluetooth_conn.h"
#include<QMessageBox>
#include"bluetooth_serial.h"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(0);
	Config_Dialog& Dialog = Config_Dialog::get_instance();
    connect(&Dialog,&Config_Dialog::open_serial,this,&MainWindow::open_bluetooth_serial);
	connect(&Dialog, &Config_Dialog::update_settings, this, &MainWindow::update_setting);

#ifdef Q_OS_ANDROID
	joystick = new Joystick(nullptr, 300);
#else
	joystick = new Joystick();
#endif
	ui->formLayout_2->addWidget(joystick);
	route_widget = new route();
	ui->formLayout_3->addWidget(route_widget);
	route_widget->show();

}

MainWindow::~MainWindow() {
	delete route_widget;
	if (b_conn) {
		b_conn->close();
		delete b_conn;
	}

	delete joystick;
	delete ui;
}

void MainWindow::on_pushButton_7_clicked() {
    Config_Dialog& Dialog = Config_Dialog::get_instance();
	Dialog.set_position(this);
    Dialog.activateWindow();
	Dialog.show();

}
void MainWindow::update_setting(config c) {
	ui->frame_7->setVisible(c.show_speed);
	ui->stackedWidget->setCurrentIndex(c.choice);
	route_widget->geo.clear();
}

void MainWindow::on_pushButton_6_clicked() {
	if (connected_socket) {
		QMessageBox msgbox(QMessageBox::Warning, "警告", "要断开连接吗", QMessageBox::Ok | QMessageBox::Cancel, this);
		int ret = msgbox.exec();
		if (ret == QMessageBox::Ok) {
			connected_socket->abort();
			delete connected_socket;
            connected_socket = nullptr;
            ui->car_icon->setPixmap(QPixmap(":/res/ic_fluent_vehicle_car_collision_24_regular.png"));
            ui->pushButton_6->setText("连接");
            ui->label->setText("N/A");
			return;
		} else return;

	}

	if (!b_conn) {
		b_conn = new Bluetooth_conn(this);
        connect(b_conn, &Bluetooth_conn::connected, this, &MainWindow::socket_connected);
	} else {
		b_conn->on_scan_btn_clicked();
		b_conn->showNormal();
	}
	b_conn->show();
}


void MainWindow::on_stop_btn_clicked() {
	ui->Speed_Slider->setValue(0);
}
void MainWindow::set_battery_value(const int& value) {
	ui->label_3->setText(QString::number(value) + "%");
	ui->battery_icon->setPixmap(QPixmap(":/res/ic_fluent_battery_" + QString::number(value / 10) + "_24_regular.png"));
}

void MainWindow::on_stop_btn_2_clicked() {
	on_stop_btn_clicked();
}

void MainWindow::socket_connected(QBluetoothSocket* s, const QString &name, const QString &addr) {
    ui->car_icon->setPixmap(QPixmap(":/res/ic_fluent_vehicle_car_48_regular.png"));
	connected_socket = s;
    connect(connected_socket,&QBluetoothSocket::readyRead,[this](){rec_data(connected_socket->readAll());});
    connect(connected_socket,&QBluetoothSocket::errorOccurred,this,&MainWindow::socket_disconnected);
    ui->pushButton_6->setText("已连接");
	ui->label->setText(name);
    Address=addr;
}
void MainWindow::print(const QString& info) {
	ui->textBrowser->append(info);
}
void MainWindow::rec_data(const QString& data){
    qDebug()<<data;
    print(data);

}
void MainWindow::socket_disconnected(){
    connected_socket=nullptr;
    ui->car_icon->setPixmap(QPixmap(":/res/ic_fluent_vehicle_car_collision_24_regular.png"));
    ui->pushButton_6->setText("连接");
    ui->label->setText("N/A");
    QMessageBox msgbox(QMessageBox::Warning, "警告", "连接已断开", QMessageBox::Ok, this);
    msgbox.exec();
}
void MainWindow::open_bluetooth_serial(){
    if(connected_socket){
    bluetooth_serial* b=new bluetooth_serial(this);
    b->show();
    }
}
