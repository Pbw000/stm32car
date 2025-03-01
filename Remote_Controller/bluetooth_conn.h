#ifndef BLUETOOTH_CONN_H
#define BLUETOOTH_CONN_H
#include<QBluetoothDeviceDiscoveryAgent>
#include <QWidget>
#include<QDialog>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>
#include<QPushButton>
namespace Ui {
class Bluetooth_conn;
}

class Bluetooth_conn : public QDialog
{
    Q_OBJECT
    friend class MainWindow;
signals:
    void connected(QBluetoothSocket* connected_socket,QString Device_Name,QString addr);
public:
    explicit Bluetooth_conn(QWidget *parent = nullptr);
    ~Bluetooth_conn();
private slots:
    void additem(const QBluetoothDeviceInfo&);
    void make_connection(QPointer<QPushButton>, const QString &, const QString&);
    void on_scan_btn_clicked();

private:
    Ui::Bluetooth_conn *ui;
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
};

#endif // BLUETOOTH_CONN_H
