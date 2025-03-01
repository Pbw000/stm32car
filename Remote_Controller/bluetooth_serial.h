#ifndef BLUETOOTH_SERIAL_H
#define BLUETOOTH_SERIAL_H
#include<QBluetoothSocket>
#include <QDialog>

namespace Ui {
class bluetooth_serial;
}

class bluetooth_serial : public QDialog
{
    Q_OBJECT

public:
    explicit bluetooth_serial(QWidget *parent = nullptr);
    ~bluetooth_serial();

private slots:
    void on_send_btn_clicked();

private:
    Ui::bluetooth_serial *ui;
    QBluetoothSocket* socket_serial=nullptr;
};

#endif // BLUETOOTH_SERIAL_H
