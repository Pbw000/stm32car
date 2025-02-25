#ifndef BLUETOOTH_CONN_H
#define BLUETOOTH_CONN_H

#include <QWidget>

namespace Ui {
class Bluetooth_conn;
}

class Bluetooth_conn : public QWidget
{
    Q_OBJECT

public:
    explicit Bluetooth_conn(QWidget *parent = nullptr);
    ~Bluetooth_conn();

private:
    Ui::Bluetooth_conn *ui;
};

#endif // BLUETOOTH_CONN_H
