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

private slots:
    void VisionTreeListSelectionChanged(QObject *newselection);
    void InspectionInserted(QModelIndex index, int start, int end);


    void on_bt_toogleSideMenu_clicked(bool checked);

private:
    Ui::VisionWindow *ui;
    VisionSettings* m_visionsettings;
    ConfigurationsWidget *configs;
    QLayout *m_modulelayout;
    KPPVision *vision;
};

#endif // VISIONWINDOW_H
