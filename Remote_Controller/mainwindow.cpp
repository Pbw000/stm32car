#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config_dialog.h"
#include"route.h"
#include"bluetooth_conn.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    Config_Dialog& Dialog=Config_Dialog::get_instance();
    connect(&Dialog, &Config_Dialog::update_settings, this, &MainWindow::update_setting);

#ifdef Q_OS_ANDROID
    joystick=new Joystick(nullptr,300);
#else
    joystick=new Joystick();
#endif
    ui->formLayout_2->addWidget(joystick);
    route_widget=new route();
    ui->formLayout_3->addWidget(route_widget);
    route_widget->show();

}

MainWindow::~MainWindow()
{   delete route_widget;
    if(b_conn){
        b_conn->close();
        delete b_conn;
    }

    delete joystick;
    delete ui;
}

void MainWindow::on_pushButton_7_clicked()
{Config_Dialog& Dialog=Config_Dialog::get_instance();
    Dialog.set_position(this);
    Dialog.show();

}
void MainWindow::update_setting(config c){
    ui->frame_7->setVisible(c.show_speed);
    ui->stackedWidget->setCurrentIndex(c.choice);
    route_widget->geo.clear();
}

void MainWindow::on_pushButton_6_clicked()
{   if(!b_conn)b_conn=new Bluetooth_conn();
    else {b_conn->on_scan_btn_clicked();
        b_conn->showNormal();}
    b_conn->show();
    ui->car_icon->setPixmap(QPixmap(":/res/ic_fluent_vehicle_car_collision_24_regular.png"));
}


void MainWindow::on_stop_btn_clicked()
{
 ui->Speed_Slider->setValue(0);
}
void MainWindow::set_battery_value(const int& value){
    ui->label_3->setText(QString::number(value)+"%");
    ui->battery_icon->setPixmap(QPixmap(":/res/ic_fluent_battery_"+QString::number(value/10)+"_24_regular.png"));
}

void MainWindow::on_stop_btn_2_clicked()
{
    on_stop_btn_clicked();
}

