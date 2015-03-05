#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
    {
 //   setWindowModality(Qt::WindowModal);

    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint) ;
}

QString LoginWindow::getUser()
{
    return ui->__txt_user->text();
}

QString LoginWindow::getPass()
{
    return ui->__txt_pass->text();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on___bt_ok_clicked()
{
    accept();
    this->close();
}

void LoginWindow::on___bt_cancel_clicked()
{
    reject();
    this->close();
}
