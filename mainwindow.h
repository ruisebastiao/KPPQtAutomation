#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configurationswidget.h"
#include "QToolButton"
#include "kppvision.h"
#include "visionwindow.h"
#include "QDebug"
#include "actionbar.h"
#include "qlineedit.h"
#include "crashdialog.h"
#include "type_traits"
#include "QDesktopWidget"
#include "swipegesturerecognizer.h"
#include "kppcommon.h"
#include "loginwindow.h"
#include "applicationsettingswindow.h"
#include "applicationsettings.h"

//using namespace Vision;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    static ApplicationSettings *applicationSettings;

    ~MainWindow();

private slots:
    void ActionButtonClicked(QToolButton *buttonClicked);
    void MenuActionClicked(QAction* actionmenu);

    void bt_Cliked();


    void LoadDone(QObject *Sender);


public slots:
    void focusChanged(QWidget* old, QWidget* now);
    void UserLevelChanged(ApplicationSettings::UserLevel newlevel);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;

    bool FirstRun;

    VisionWindow* visionmodule;
    ApplicationSettingsWindow *appsettingsWindow=0;
    void SetupSideMenu();
    bool IsLineEdit(const QWidget *widget);
};

#endif // MAINWINDOW_H
