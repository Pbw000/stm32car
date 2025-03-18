#ifndef CONFIG_DIALOG_H
#define CONFIG_DIALOG_H
#include <QDialog>
#include "mainwindow.h"
#include<QDialog>
namespace Ui {
class Config_Dialog;
}

class Config_Dialog : public QDialog
{
    Q_OBJECT

public:
    void set_position(QWidget *parent_window);
    explicit Config_Dialog(QWidget *parent = nullptr);
    static Config_Dialog&  get_instance();

private slots:
    void on_accept_btn_clicked();
    void on_cancel_btn_clicked();

    void on_reset_btn_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();


    void on_open_bluetooth_serial_clicked();

    void on_about_clicked();

private:
MainWindow::config c;
    Ui::Config_Dialog *ui;
~Config_Dialog(){};
signals:
    void update_settings(MainWindow::config cfg);
    void open_serial();
};

#endif // CONFIG_DIALOG_H
