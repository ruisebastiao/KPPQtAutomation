#ifndef KPPGESTUREFRAME_H
#define KPPGESTUREFRAME_H


#include <QWidget>
#include <QFrame>

class KPPGestureFrame : public QFrame
{
    Q_OBJECT
public:
    explicit KPPGestureFrame(QWidget *parent = 0);

signals:

public slots:


    // QObject interface
public:
    //bool event(QEvent *pEvent);
};

#endif // KPPGESTUREFRAME_H
