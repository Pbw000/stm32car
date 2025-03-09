#include "bluetooth_serial.h"
#include "ui_bluetooth_serial.h"
#include"mainwindow.h"
bluetooth_serial::bluetooth_serial(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::bluetooth_serial)
{
    ui->setupUi(this);

    socket_serial=static_cast<MainWindow>(parent).connected_socket;
}
bluetooth_serial::~bluetooth_serial()
{
    delete ui;
}

void bluetooth_serial::on_send_btn_clicked()
{
    if(socket_serial){
        socket_serial->write(ui->lineEdit->text().toStdString().c_str());
    }
    ui->textBrowser->append(ui->lineEdit->text());
}

