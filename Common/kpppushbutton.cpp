#include "kpppushbutton.h"
#include "QResizeEvent"
#include "QApplication"
#include "QThread"
#include "qdebug.h"
#include "qwidgetaction.h"
#include "qaction.h"


KPPPushButton::KPPPushButton(QWidget *parent) :
    QPushButton(parent),
    isSelected(false),
    m_menu(0),
    m_MenuActivationFlags(KPPPushButton::None)

{
    ishover=false;
    defaultSize=0;
    m_visible=false;
  //  setVisible(true);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    this->setStyleSheet("QPushButton {\
                                border: 1px solid #6593cf;\
                                border-radius: 2px;\
                                padding: 5px 15px 2px 5px;\
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,\
                                        stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);\
                                color: #006aff;\
                                font: bold large 'Arial';\
                                height: 30px;\
                        }\
                        QPushButton:hover,QPushButton:hover:on{\
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #ffd9aa,\
                                        stop :   0.5 #ffbb6e, stop :   0.55 #feae42, stop :   1.0 #fedb74);\
                        }\
                        QPushButton:pressed {\
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #c0dbff,\
                                stop :   0.5 #cfd26f, stop :   0.55 #c7df6f, stop :   1.0 #f5f9ff);\
                                padding-top: 2px;\
                                padding-left: 3px;\
                        }\
                        QPushButton:on {\
                                    border: 1px solid #6593cf;\
                                    background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #BDD2AE,\
                                    stop :   0.5 #E0F3D2, stop :   0.55 #E0F3D2, stop :   1.0 #BDD2AE);\
                        }\
                        QPushButton:disabled {\
                                background: transparent #e5e9ee;\
                                padding-top: 2px;        \
                                padding-left: 3px;\
                                color: black;\
                        }\
                        ");




             //addmoduleaction->setObjectName("bt_addvisionmodule");

}

KPPPushButton::~KPPPushButton()
{
    setVisible(false);
    //QThread::sleep(300);
}

/*
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #5AA72D,\
                                stop :   0.5 #B3E296, stop :   0.55 #B3E296, stop :   1.0 #f5f9ff);\
                                padding-top: 2px;\
                                padding-left: 3px;\
*/

void KPPPushButton::paintEvent (QPaintEvent *)
{


   // QStyleOptionButton option;
   //  option.init(this);



     //QPainter painter(this);

     //paintEvent(QPaintEvent *paint)
       //  {
              QStyleOption opt;
              opt.init(this);
              QPainter p(this);

              if(isDown()){
                 opt.state |= QStyle::State_Sunken;
              }
              else{
                  // option.state =QStyle::State_Off|QStyle::State_Raised;
              }


              if (isSelected)
                  opt.state|= QStyle::State_On;
              else
                  opt.state|= QStyle::State_Off;
              //option.text = text();
              //option.icon = icon();


             //Draw the base
              style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

             //Draw the text
              style()->drawItemText(&p,this->rect(),Qt::AlignCenter,(this->palette()), true, this->text());

              if(!this->icon().isNull())
                 //Draw the icon at 75% button height
                 style()->drawItemPixmap(&p, this->rect(),Qt::AlignLeft|Qt::AlignVCenter, this->icon().pixmap(this->rect().height()  * 0.75));

         //}

     //style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

}


void KPPPushButton::setVisible(bool visible)
{
    if(visible==m_visible) return;
    m_visible=visible;
    //QSize temp=size()


    if(defaultSize==0){
        defaultSize= 2000;//parentWidget()->geometry().size().width();
    }
    //bool teste=isHidden();
    int start=0;

    int end=defaultSize;
    animation1 = new QPropertyAnimation(this, "maximumWidth");
    connect(animation1,SIGNAL(finished()),this,SLOT(AnimationFinished()));

    //int factor=abs(defaultSize-maximumWidth());

    animation1->setEasingCurve(QEasingCurve::OutCirc);
    animation1->setStartValue(start);
    animation1->setEndValue(end);
    if(visible){
        animation1->setDuration(300);
        QPushButton::setVisible(visible);
        animation1->setDirection(QAbstractAnimation::Forward);
    }
    else{
        animation1->setDuration(300);
        animation1->setEndValue(width());
        animation1->setDirection(QAbstractAnimation::Backward);
    }


    animation1->start(QAbstractAnimation::DeleteWhenStopped);

 //   QPushButton::setVisible(visible);

}



void KPPPushButton::setSelected(bool selected)
{
    this->isSelected=selected;
    this->repaint();
}

void KPPPushButton::AddSubMenu(QString Text,QString Name)
{

    if(m_menu==0){
        m_menu=new QMenu(this);
        m_menu->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    }

    QWidgetAction *new_action= new QWidgetAction(m_menu);
    KPPActionPushButton* action_widgetbt = new KPPActionPushButton(this,m_menu);
    action_widgetbt->setText(Text);
    new_action->setDefaultWidget(action_widgetbt);

     QList<QAction*> *menu_actions= new QList<QAction*>();
     menu_actions->append(new_action);
     m_menu->addActions(*menu_actions);


     action_widgetbt->setObjectName(Name);
     connect( action_widgetbt, SIGNAL(clicked()), this, SLOT(SubMenuClickedSlot()));

}

void KPPPushButton::setMenuActivation(KPPPushButton::MenuActivationFlag ActivationFlags)
{
    m_MenuActivationFlags=ActivationFlags;
    switch (m_MenuActivationFlags) {

    case None:
        ungrabGesture(Qt::SwipeGesture);
        setMenu(0);
        break;
    case Click:
        setMenu(m_menu);
        break;
    case Gesture:
        grabGesture(Qt::SwipeGesture);

        break;
    default:
        break;
    }



}

void KPPPushButton::SubMenuClickedSlot()
{
    QObject* sender=QObject::sender();
    emit SubMenuClicked(sender);
}

void KPPPushButton::AnimationFinished(){
    QPushButton::setVisible(m_visible);
    parentWidget()->update();
}


void KPPPushButton::enterEvent(QEvent *e)
{
    ishover=true;
    QPushButton::enterEvent(e);
}

void KPPPushButton::leaveEvent(QEvent *e)
{
    ishover=false;
    QPushButton::leaveEvent(e);
}

bool KPPPushButton::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture) {
      return OnGestureEvent(static_cast<QGestureEvent*>(event));
    }

    return QPushButton::event(event);
}

bool KPPPushButton::OnGestureEvent(QGestureEvent *pEvent)
{
    if ( QGesture *pSwipe = pEvent->gesture(Qt::SwipeGesture)) {
        OnSwipeGesture(static_cast<QSwipeGesture*>(pSwipe));
    } else {
        qDebug("Unexpected gesture detected. We only grab Qt::SwipeGesture ");
    }

    return true;
}

bool KPPPushButton::OnSwipeGesture(QSwipeGesture *pSwipe)
{
    // Do something as result of the gesture
    Qt::GestureState state=pSwipe->state();
    if (state == Qt::GestureFinished) {

        qreal  swipeangle=pSwipe->swipeAngle();
        qDebug()<<"Angle:"<<pSwipe->swipeAngle();
        if (pSwipe->horizontalDirection() == QSwipeGesture::Left &&
                (swipeangle>150 && swipeangle<210)){


        }
        else if(pSwipe->horizontalDirection() == QSwipeGesture::Right &&
                ( (swipeangle>=0 && swipeangle<15) || (swipeangle>300 && swipeangle<=360))){

        }
        else if(pSwipe->verticalDirection() == QSwipeGesture::Down ){
            if((swipeangle>=240 && swipeangle<280)){
                setMenu(m_menu);
                click();
                setMenu(0);
            }
        }

    }
    return true;
}






void KPPPushButton::showEvent(QShowEvent *)
{
    if(m_visible){

    }
}


void KPPPushButton::mousePressEvent(QMouseEvent *e)
{
//    switch (m_MenuActivationFlags) {

//    case None:

//        break;
//    case Click:

//        break;
//    case Gesture:

//        break;
//    default:
//        break;
//    }
//    e->setAccepted(false);
    QPushButton::mousePressEvent(e);

}
