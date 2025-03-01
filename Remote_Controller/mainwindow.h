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
        choice choice;
    };
    void print(const QString &info);

private slots:
    void on_pushButton_7_clicked();
    void rec_data(const QString& data);
    void on_pushButton_6_clicked();
    void set_battery_value(const int&);
    void on_stop_btn_clicked();
    void update_setting(config c);
    void socket_connected(QBluetoothSocket*, const QString&,const QString&);
    void on_stop_btn_2_clicked();
    void socket_disconnected();
    void open_bluetooth_serial();
private:
    QBluetoothSocket* connected_socket=nullptr;
    QString Address;
    route* route_widget;
    Joystick* joystick;
    Bluetooth_conn* b_conn=nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
