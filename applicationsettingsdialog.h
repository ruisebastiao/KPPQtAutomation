#ifndef APPLICATIONSETTINGSDIALOG_H
#define APPLICATIONSETTINGSDIALOG_H

#include <QDialog>
#include "applicationsettings.h"
#include "ui_applicationsettingsdialog.h"

namespace Ui {
class ApplicationSettingsDialog;
}

class ApplicationSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicationSettingsDialog(QWidget *parent = 0,ApplicationSettings* appsettings=0);
    ~ApplicationSettingsDialog();
    //Ui::ApplicationSettingsDialog *getUI();
private slots:
    void on___bt_exit_clicked();
    void on___bt_save_clicked();

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on___bt_removemodule_clicked();

    void on___bt_addmodule_clicked();
    void MenuActionButtonTriggered();
private:
    Ui::ApplicationSettingsDialog *ui;
    ApplicationSettings* m_appsettings;

    // QWidget interface
public slots:
    void setVisible(bool visible);
};

#endif // APPLICATIONSETTINGSDIALOG_H
