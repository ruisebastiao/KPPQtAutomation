#ifndef KPPEDITBOX_H
#define KPPEDITBOX_H

#include <QWidget>

#include "QLineEdit"


class  KPPEditBox : public QLineEdit
{
    Q_OBJECT
public:
    explicit KPPEditBox(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
   // void paintEvent(QPaintEvent *);
};

#endif // KPPEDITBOX_H
