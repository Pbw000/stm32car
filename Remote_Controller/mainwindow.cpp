#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config_dialog.h"
#include"route.h"
#include"bluetooth_conn.h"
#include<QMessageBox>
#include"bluetooth_serial.h"
#include<QTimer>
#include<QThread>
#include <cstdint>

class STM32CRC {
private:
    uint32_t crc;
    static constexpr uint32_t Polynomial = 0x04C11DB7;  // STM32固定多项式

    // 处理单个字节（MSB first）
    void process_byte(uint8_t byte) {
        for (int i = 0; i < 8; ++i) {
            bool bit = (byte >> (7 - i)) & 0x1;  // 从最高位开始取位
            bool msb = (crc >> 31) & 0x1;
            crc = (crc << 1) | bit;  // 左移并插入新位
            if (msb ^ bit) {
                crc ^= Polynomial;    // 异或多项式
            }
        }
    }

public:
    STM32CRC() : crc(0xFFFFFFFF) {}  // 初始值固定为0xFFFFFFFF

    // 复位CRC寄存器
    void reset() {
        crc = 0xFFFFFFFF;
    }

    // 输入32位数据（模拟STM32的CRC->DR写入）
    void update(uint32_t data) {
        // 分解为4个字节（大端顺序：高字节在前）
        process_byte((data >> 24) & 0xFF);  // 最高字节
        process_byte((data >> 16) & 0xFF);
        process_byte((data >> 8)  & 0xFF);
        process_byte( data        & 0xFF);  // 最低字节
    }

    // 获取计算结果的低8位
    uint8_t get() const {
        return static_cast<uint8_t>(crc & 0xFF);
    }
};

// 计算两个uint8_t的CRC-8校验和
uint8_t ComputeCRC8(uint8_t data1, uint8_t data2) {
    STM32CRC crc;
    // 组合成32位数据：高16位为输入，低16位补零
    uint32_t input = (static_cast<uint32_t>(data1) << 24) |
                     (static_cast<uint32_t>(data2) << 16);
    crc.update(input);
    return crc.get();
}

#define RateLimint 60
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_3->setShortcut(QKeySequence(Qt::Key_Up));
    ui->pushButton_4->setShortcut(QKeySequence(Qt::Key_Down));
    ui->pushButton->setShortcut(QKeySequence(Qt::Key_Left));
    ui->pushButton_2->setShortcut(QKeySequence(Qt::Key_Right));
    ui->speed_indicator->setValue(0);
    tmr->setInterval(20);
    connect(tmr,&QTimer::timeout,this,&MainWindow::change_velocity);
    connect(tmr1,&QTimer::timeout,this,&MainWindow::send_velocity);
	Config_Dialog& Dialog = Config_Dialog::get_instance();
    connect(&Dialog,&Config_Dialog::open_serial,this,&MainWindow::open_bluetooth_serial);
	connect(&Dialog, &Config_Dialog::update_settings, this, &MainWindow::update_setting);

#ifdef Q_OS_ANDROID
	joystick = new Joystick(nullptr, 300);
#else
	joystick = new Joystick();
#endif
    connect(joystick,&Joystick::positionChanged,[&](const int& v1,const int& v2){
        velocity_x=v1;
        velocity_y=v2;
    });
	ui->formLayout_2->addWidget(joystick);
	route_widget = new route();
	ui->formLayout_3->addWidget(route_widget);
	route_widget->show();
 tmr1->start(Interval);
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
void MainWindow::send_velocity(){

    int v1,v2;
    v1=velocity_x+velocity_y;
    if(v1>RateLimint)v1=RateLimint;
    else if(v1<-RateLimint)v1=-RateLimint;
    v2=velocity_y-velocity_x;
    if(v2>RateLimint)v2=RateLimint;
    else if(v2<-RateLimint)v2=-RateLimint;
    uint8_t data1 = v1+100;
    uint8_t data2 = v2+100;
    uint8_t result = ComputeCRC8(data1, data2);
    char command[4]={static_cast<char>(0xFF),static_cast<char>(data1),static_cast<char>(data2),static_cast<char>(static_cast<int>(result))};

    qDebug()<<v1<<v2<<static_cast<int>(result);
    if(connected_socket){
        connected_socket->write(command);
    }
    else{
        tmr1->stop();
    }
}
void MainWindow::on_pushButton_7_clicked() {
    Config_Dialog& Dialog = Config_Dialog::get_instance();
	Dialog.set_position(this);
    Dialog.activateWindow();
	Dialog.show();

}
void MainWindow::update_setting(config c) {
	ui->frame_7->setVisible(c.show_speed);
    ui->stackedWidget->setCurrentIndex(c.config_choice);
	route_widget->geo.clear();
    Interval=c.interval;
    tmr1->stop();
    tmr1->start(Interval);

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

void MainWindow::set_battery_value(const int& value) {
	ui->label_3->setText(QString::number(value) + "%");
	ui->battery_icon->setPixmap(QPixmap(":/res/ic_fluent_battery_" + QString::number(value / 10) + "_24_regular.png"));
}

void MainWindow::on_stop_btn_2_clicked() {
    velocity_x=0;
      velocity_y=0;
}

void MainWindow::socket_connected(QBluetoothSocket* s, const QString &name, const QString &addr) {
    ui->car_icon->setPixmap(QPixmap(":/res/ic_fluent_vehicle_car_48_regular.png"));
	connected_socket = s;
    connect(connected_socket,&QBluetoothSocket::readyRead,[&](){rec_data(connected_socket->readAll());});
    connect(connected_socket,&QBluetoothSocket::errorOccurred,this,&MainWindow::socket_disconnected);
    ui->pushButton_6->setText("已连接");
	ui->label->setText(name);
    Address=addr;
    tmr1->start(Interval);
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

void MainWindow::on_pushButton_3_pressed()
{//up
    if(is_y_pressed)return;
    else is_y_pressed=1;
    tmr->start();
    velocity_y++;
}
void MainWindow::on_pushButton_4_pressed()
{//down
    if(is_y_pressed)return;
    else is_y_pressed=-1;
    tmr->start();
    velocity_y--;
}


void MainWindow::on_pushButton_pressed()
{//left
    if(is_x_pressed)return;
    else is_x_pressed=-1;
    tmr->start();
    velocity_x--;
}


void MainWindow::on_pushButton_2_pressed()
{//right
    if(is_x_pressed)return;
    else is_x_pressed=1;
    tmr->start();
    velocity_x++;
}


void MainWindow::on_pushButton_3_released()
{
    is_y_pressed=0;
}


void MainWindow::on_pushButton_released()
{
    is_x_pressed=0;
}


void MainWindow::on_pushButton_4_released()
{
    is_y_pressed=0;
}


void MainWindow::on_pushButton_2_released()
{
    is_x_pressed=0;
}

void MainWindow::change_velocity(){
    if(!is_x_pressed){
        velocity_x/=2;
    }
    else if(velocity_x<=100&&velocity_x>=-100){
        velocity_x+=is_x_pressed;
    }
    if(!is_y_pressed){
        velocity_y/=2;
    }
    else if(velocity_y<=100&&velocity_y>=-100){
         velocity_y+=is_y_pressed;
    }
    int speed=sqrt(velocity_x*velocity_x+velocity_y*velocity_y);
    if(speed<=100)ui->speed_indicator->setValue(speed);
    if(!(velocity_x|velocity_y|is_x_pressed|is_y_pressed)){
        tmr->stop();}
}

void MainWindow::on_submit_btn_clicked()
{ui->submit_btn->setEnabled(false);
    route_widget->enable=false;
    auto ptr=&route_widget->geo;
    route::geometry* pre=new route::geometry(route_widget->geo.front());
    QTimer* u_timer=new QTimer(this);
    u_timer->setInterval(Interval);
    u_timer->start();
    connect(u_timer,&QTimer::timeout,[u_timer,ptr,pre,this](){

            while(!ptr->empty()){
                if(*pre-ptr->front()<10){
                    ptr->pop_front();}
                else break;
            }
            if(!ptr->empty()){
            qDebug()<<(ptr->front().x-pre->x)<<(pre->y)-(ptr->front().y)<<ptr->front().x<<pre->x<<pre->y<<ptr->front().y;
             //send_velocity(ptr->front().x-pre->x,pre->y-ptr->front().y);
            *pre=ptr->front();
            ptr->pop_front();
            route_widget->repaint();
        }
        else{
            route_widget->repaint();
            u_timer->stop();
            ui->submit_btn->setEnabled(true);
            delete u_timer;
            route_widget->enable=true;
        }
    });


}

