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
    explicit VisionWindow(QWidget *parent = 0);
    ~VisionWindow();
    void toogleModuleSettings();

private slots:
    void VisionTreeListSelectionChanged(QObject *newselection);
    void InspectionInserted(QModelIndex index, int start, int end);


    void on_bt_toogleSideMenu_clicked(bool checked);

private:
    Ui::VisionWindow *ui;
    VisionSettings *settings;
    ConfigurationsWidget *configs;
    KPPVision *vision;
};

#endif // VISIONWINDOW_H
