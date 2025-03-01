#include "config_dialog.h"
#include "ui_config_dialog.h"

Config_Dialog::Config_Dialog(QWidget *parent)
    :QDialog(parent),ui(new Ui::Config_Dialog)
{    c.show_speed=true;
    c.choice=MainWindow::btn;
    ui->setupUi(this);
    ui->checkBox->setChecked(c.show_speed);
    ui->radioButton_2->setChecked(true);
}

Config_Dialog::~Config_Dialog()
{
    delete ui;
}
void Config_Dialog::set_position(QWidget *parent_window){
#ifdef Q_OS_ANDROID
this->setGeometry(parent_window->geometry());
#else
    int x=parent_window->geometry().x()+parent_window->size().width()/2-width()/2;
    int y=parent_window->geometry().y()+parent_window->size().height()/2-height()/2;
    this->setGeometry(QRect(x,y,width(),height()));
    this->showNormal();
#endif


}
Config_Dialog& Config_Dialog::get_instance(){
    static Config_Dialog Dialog;
    return Dialog;
}

void Config_Dialog::on_accept_btn_clicked()
{   if(ui->radioButton->isChecked())c.choice=MainWindow::js;
    else if(ui->radioButton_2->isChecked())c.choice=MainWindow::btn;
    else c.choice=MainWindow::r;
    c.show_speed=ui->checkBox->isChecked();
    this->close();
    emit update_settings(c);

}


void Config_Dialog::on_cancel_btn_clicked()
{   switch(c.choice){
    case MainWindow::js:
        ui->radioButton->setChecked(true);
        break;
    case MainWindow::btn:
        ui->radioButton_2->setChecked(true);
        break;
    case MainWindow::r:
        ui->radioButton_3->setChecked(true);
        break;
    }
     this->close();
    ui->checkBox->setChecked(c.show_speed);
}



void Config_Dialog::on_reset_btn_clicked()
{ui->radioButton_2->setChecked(true);
    ui->checkBox->setChecked(true);
}


void Config_Dialog::on_radioButton_clicked()
{
    ui->radioButton_2->setChecked(false);
     ui->radioButton_3->setChecked(false);
}


void Config_Dialog::on_radioButton_2_clicked()
{
      ui->radioButton->setChecked(false);
     ui->radioButton_3->setChecked(false);
}


void Config_Dialog::on_radioButton_3_clicked()
{
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
}

