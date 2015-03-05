#ifndef APPLICATIONSETTINGSWINDOW_H
#define APPLICATIONSETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
class ApplicationSettingsWindow;
}

class ApplicationSettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicationSettingsWindow(QWidget *parent = 0);
    ~ApplicationSettingsWindow();

private:
    Ui::ApplicationSettingsWindow *ui;
};

#endif // APPLICATIONSETTINGSWINDOW_H
