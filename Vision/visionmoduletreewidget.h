#ifndef VISIONMODULETREEWIDGET_H
#define VISIONMODULETREEWIDGET_H


#include <QTreeWidget>

#include "qlabel.h"
#include "qcombobox.h"
#include "QHeaderView"
#include "qpushbutton.h"
#include "QVBoxLayout"
#include "kpptreepushbutton.h"
#include "qpainter.h"
#include "qstyleditemdelegate.h"

class VisionModuleTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit VisionModuleTreeWidget(QWidget *parent = 0);



private:
    QComboBox* cb_capturesource;

    QVBoxLayout *layout_sourcename;
    QVBoxLayout *layout_sourcesettings;


    QFrame *frame_sourcename;
    QFrame *frame_sourcesettings;

    QTreeWidgetItem *item_sourcetype;
    QTreeWidgetItem *item_sourcename;
    QTreeWidgetItem *item_sourcesettings;





     KPPRootTreePushButton *bt_sourcename;
     KPPRootTreePushButton *bt_type;

     void Initialize_Trees();
     void UpdateSourceType();
signals:

public slots:

private slots:
  //  void cbCapturecurrentIndexChanged(QString);


public:
   // QRect visualRect(const QModelIndex &index) const;

    // QAbstractItemView interface
public:

    void DoShow();
    void DoHide();
};


#endif // VISIONMODULETREEWIDGET_H
