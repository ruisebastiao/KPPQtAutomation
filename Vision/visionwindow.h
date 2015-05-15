#ifndef VISIONWINDOW_H
#define VISIONWINDOW_H


#include <QFrame>
#include "kppvision.h"
#include "configurationswidget.h"

namespace Ui {
class VisionWindow;

}

class VisionWindow : public QFrame
{
    Q_OBJECT

public:
    explicit VisionWindow(QWidget *parent = 0, QLayout *modulelayout=0, VisionSettings *settings=0);
    ~VisionWindow();
    void toogleModuleSettings();


    void setConfigwindowVisible(bool visible=true);

private slots:
    void VisionTreeListSelectionChanged(QObject *newselection); 
    void on_bt_toogleSideMenu_clicked(bool checked);

private:
    Ui::VisionWindow *ui;
    VisionSettings* m_visionsettings;
    ConfigurationsWidget *m_configwindow;
    QLayout *m_modulelayout;
    KPPVision *vision;
};

#endif // VISIONWINDOW_H
