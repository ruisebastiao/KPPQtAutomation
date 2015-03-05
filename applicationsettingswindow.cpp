#include "applicationsettingswindow.h"
#include "ui_applicationsettings.h"

ApplicationSettingsWindow::ApplicationSettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationSettingsWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint) ;
    ui->confpage1->setDisplayed(true);
    ui->confpage2->setDisplayed(true);
}

ApplicationSettingsWindow::~ApplicationSettingsWindow()
{
    delete ui;
}
