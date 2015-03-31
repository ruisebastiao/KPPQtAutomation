#ifndef KPPPUSHBUTTON_H
#define KPPPUSHBUTTON_H


#include <QPushButton>
#include "qpropertyanimation.h"
#include "qstyleoption.h"
#include "qpainter.h"
#include <QGesture>
#include <qtoolbutton.h>
#include "kppactionpushbutton.h"

class  KPPPushButton : public QPushButton
{    
    Q_OBJECT
    Q_ENUMS(MenuActivationFlag)

public:
    enum MenuActivationFlag {
        Click=0x00,
        Gesture=0x01,
        None=0x02
    };

    explicit KPPPushButton(QWidget *parent = 0);
    ~KPPPushButton();
    virtual void paintEvent(QPaintEvent *);
    void	setVisible ( bool visible );
    //void AddGestures(Qt::GestureType type);
    void setSelected(bool selected=true);
    void AddSubMenu(QString Text, QString Name);
    void setMenuActivation(KPPPushButton::MenuActivationFlag ActivationFlags);

private:
    MenuActivationFlag m_MenuActivationFlags;
    bool ishover,resizing,m_visible;
    int defaultSize;
    bool isSelected;
    QPropertyAnimation *animation1;
    QMenu* m_menu;
signals:
    void SubMenuClicked(QObject* MenuClicked);
private slots:

    void SubMenuClickedSlot();
    void AnimationFinished();

public slots:


    // QWidget interface
protected:

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    bool event(QEvent *event);


private:
    bool OnGestureEvent(QGestureEvent* pEvent);
    bool OnSwipeGesture(QSwipeGesture* pSwipe);


};


#endif // KPPPUSHBUTTON_H
