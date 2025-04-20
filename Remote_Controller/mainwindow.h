#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"joystick.h"
#include"route.h"
#include"bluetooth_conn.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class bluetooth_serial;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum choice{
        btn,js,r
    };
    struct config{
        bool show_speed;
        bool ob_void=false;
        bool tracking=false;
        choice config_choice;
        int interval;
        int max_speed;

    };
    void print(const QString &info);

private slots:
    void on_pushButton_7_clicked();
    void rec_data(const QString& data);
    void on_pushButton_6_clicked();
    void set_battery_value(const int&);
    void update_setting(config c);
    void socket_connected(QBluetoothSocket*, const QString&,const QString&);
    void on_stop_btn_2_clicked();
    void socket_disconnected();
    void open_bluetooth_serial();
    void change_velocity();

    void send_command(const uint8_t&,const uint8_t&);
    void on_pushButton_3_pressed();

    void on_pushButton_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_released();

    void on_pushButton_released();

    void on_pushButton_4_released();

    void on_pushButton_2_released();

    void on_submit_btn_clicked();

private:
    void send_commond_with_timeout(uint8_t a,uint8_t b,QString msg);
    void send_velocity();
    bool ob_void=false;
    bool tracking=false;
    bool rec_flag=false;
    QTimer* tmr=new QTimer(this);
    QTimer* tmr1=new QTimer(this);
    QBluetoothSocket* connected_socket=nullptr;
    QString Address;
    int velocity_x=0,velocity_y=0;
    int is_x_pressed=0,is_y_pressed=0;
    int Interval=30;
    int max_speed=100;
    route* route_widget;
    Joystick* joystick;
    Bluetooth_conn* b_conn=nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
