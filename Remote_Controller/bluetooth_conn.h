#ifndef BLUETOOTH_CONN_H
#define BLUETOOTH_CONN_H
#include<QBluetoothDeviceDiscoveryAgent>
#include <QWidget>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>
namespace Ui {
class Bluetooth_conn;
}

class Bluetooth_conn : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
signals:
    void complete();
public:
    explicit Bluetooth_conn(QWidget *parent = nullptr);
    ~Bluetooth_conn();
private slots:
    void additem(const QBluetoothDeviceInfo&);
    void make_connection();
    void on_scan_btn_clicked();

private:
    Ui::Bluetooth_conn *ui;
    QBluetoothSocket* connected_socket;
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
};

#endif // BLUETOOTH_CONN_H
