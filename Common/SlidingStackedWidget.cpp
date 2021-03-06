#include "SlidingStackedWidget.h"
#include "swipegesturerecognizer.h"
#include <slidewidget.h>
#include <QDebug>

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    if (parent!=0) {
        m_mainwindow=parent;
    }
    else {
        m_mainwindow=this;
        qDebug()<<"ATTENTION: untested mainwindow case !";
    }
    //parent should not be 0; not tested for any other case yet !!
#ifdef Q_OS_SYMBIAN
#ifndef __S60_50__
    qDebug()<< "WARNING: ONLY TESTED AND 5TH EDITION";
#endif //__S60_50__
#endif //Q_OS_SYMBIAN
    //Now, initialize some private variables with default values
    m_vertical=false;
    //setVerticalMode(true);
    m_speed=500;
    m_animationtype = QEasingCurve::OutBack;  //check out the QEasingCurve documentation for different styles
    m_now=0;
    m_next=0;
    m_wrap=false;
    m_pnow=QPoint(0,0);
    m_active=false;
    //installEventFilter(this);
    grabGesture(Qt::SwipeGesture);

    QGestureRecognizer* pRecognizer = new SwipeGestureRecognizer();
    grabGesture(QGestureRecognizer::registerRecognizer(pRecognizer));


}


bool
SlidingStackedWidget::OnSwipeGesture(QSwipeGesture* pSwipe)
{
    // Do something as result of the gesture
    if (pSwipe->state() == Qt::GestureFinished) {

        qreal  swipeangle=pSwipe->swipeAngle();
        qDebug()<<"Angle:"<<pSwipe->swipeAngle();
        if (pSwipe->horizontalDirection() == QSwipeGesture::Left &&
                (swipeangle>150 && swipeangle<210)){
            //goPrevImage();
            slideInNext(-1);
        }
        else if(pSwipe->horizontalDirection() == QSwipeGesture::Right &&
                ( (swipeangle>=0 && swipeangle<15) || (swipeangle>275 && swipeangle<=360))){
            slideInPrev(-1);
        }
        else if(pSwipe->verticalDirection() == QSwipeGesture::Down ){
            //( (swipeangle>=0 && swipeangle<15) || (swipeangle>275 && swipeangle<=360))){
            if (swipeangle>=0) {
                return true;
            }
        }
        return true;
    }
    return false;
}

bool
SlidingStackedWidget::OnGestureEvent(QGestureEvent* pEvent)
{
    QGesture *pSwipe = pEvent->gesture(Qt::SwipeGesture);
    if (pSwipe != NULL) {
        return OnSwipeGesture(static_cast<QSwipeGesture*>(pSwipe));
    } else {
        qDebug("Unexpected gesture detected. We only grab Qt::SwipeGesture ");
        return QWidget::event(pEvent);
    }
}

//QString EnumSocketTypeToString(int value)
//{
//    QMetaObject obj = QChildEvent::staticMetaObject;
//    QMetaEnum en = obj.enumerator(0);
//    return QLatin1String(en.valueToKey(value));
//}

//bool SlidingStackedWidget::eventFilter( QObject* target, QEvent* e)
//{
//    switch (e->type())
//    {
//    case QEvent::ChildAdded:
//        {
//            QChildEvent* ce = (QChildEvent*)e;
//            ce->child()->installEventFilter(this);
//        }
//        break;

//    case QEvent::ChildRemoved:
//        {
//            QChildEvent* ce = (QChildEvent*)e;
//            ce->child()->removeEventFilter(this);
//        }
//        break;
//    }

//    return QWidget::eventFilter(target, e);
//}

//void SlidingStackedWidget::childEvent(QChildEvent *event){
//   // qDebug()<<"Child :"<<event->child()->objectName();
//    //qDebug()<<"Child event:"<<EnumSocketTypeToString(event->type());

//}



bool SlidingStackedWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture ||event->type() == QEvent::GestureOverride) {
        return OnGestureEvent(static_cast<QGestureEvent*>(event));
    }

    return QWidget::event(event);
}



SlidingStackedWidget::~SlidingStackedWidget(){
}

void SlidingStackedWidget::setVerticalMode(bool vertical) {
    m_vertical=vertical;
}

void SlidingStackedWidget::setSpeed(int speed) {
    m_speed = speed;
}

void SlidingStackedWidget::setAnimation(enum QEasingCurve::Type animationtype) {
    m_animationtype = animationtype;
}

void SlidingStackedWidget::setWrap(bool wrap) {
    m_wrap=wrap;
}

void SlidingStackedWidget::slideInNext(int next=-1) {

    int now=currentIndex();
    if (next!=-1) {
        now=next;
    }
    if (m_wrap||(now<count()-1)){
        // count is inherit from QStackedWidget
        SlideWidget *widg=qobject_cast<SlideWidget*>(widget(now+1));



        if (widg->Displayed()==false) {
            slideInNext(now+1);
        }
        else
            slideInIdx(now+1);
    }
}


void SlidingStackedWidget::slideIn(t_SwipeDirection SwipeDirection) {
    switch (SwipeDirection) {
    case SwLeft:
        slideInNext(-1);
        break;
    case SwRight:
        slideInPrev(-1);
        break;
    default:
        break;
    }
}

void SlidingStackedWidget::slideInPrev(int next=-1) {
    int now=currentIndex();
    if (next!=-1) {
        now=next;
    }
    if (m_wrap||(now>0)){
        SlideWidget *widg=qobject_cast<SlideWidget*>(widget(now-1));

        if (widg!=0) {

            if (widg->Displayed()==false) {
                slideInPrev(now-1);
            }
            else
                slideInIdx(now-1);
        }
    }
}

void SlidingStackedWidget::slideInIdx(int idx, enum t_direction direction) {
    //int idx, t_direction direction=AUTOMATIC
    if (idx>count()-1) {
        direction=m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
        idx=(idx)%count();
    }
    else if (idx<0) {
        direction= m_vertical ? BOTTOM2TOP: LEFT2RIGHT;
        idx=(idx+count())%count();
    }


    slideInWgt(widget ( idx ),direction);
    //widget() is a function inherited from QStackedWidget
}


void SlidingStackedWidget::slideInWgt(QWidget * newwidget, enum t_direction  direction) {

    if (m_active) {
        return; // at the moment, do not allow re-entrance before an animation is completed.
        //other possibility may be to finish the previous animation abrupt, or
        //to revert the previous animation with a counter animation, before going ahead
        //or to revert the previous animation abrupt
        //and all those only, if the newwidget is not the same as that of the previous running animation.
    }
    else m_active=true;

    enum t_direction directionhint;
    int now=currentIndex();		//currentIndex() is a function inherited from QStackedWidget
    int next=indexOf(newwidget);
    if (now==next) {
        m_active=false;
        return;
    }
    else if (now<next){
        directionhint=m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
    }
    else {
        directionhint=m_vertical ? BOTTOM2TOP : LEFT2RIGHT;
    }
    if (direction == AUTOMATIC) {
        direction=directionhint;
    }
    //NOW....
    //calculate the shifts

    int offsetx=frameRect().width(); //inherited from mother
    int offsety=frameRect().height();//inherited from mother

    //the following is important, to ensure that the new widget
    //has correct geometry information when sliding in first time
    widget(next)->setGeometry ( 0,  0, offsetx, offsety );

    if (direction==BOTTOM2TOP)  {
        offsetx=0;
        offsety=-offsety;
    }
    else if (direction==TOP2BOTTOM) {
        offsetx=0;
        //offsety=offsety;
    }
    else if (direction==RIGHT2LEFT) {
        offsetx=-offsetx;
        offsety=0;
    }
    else if (direction==LEFT2RIGHT) {
        //offsetx=offsetx;
        offsety=0;
    }
    //re-position the next widget outside/aside of the display area
    QPoint pnext=widget(next)->pos();
    QPoint pnow=widget(now)->pos();
    m_pnow=pnow;

    widget(next)->move(pnext.x()-offsetx,pnext.y()-offsety);
    //make it visible/show
    widget(next)->show();
    widget(next)->raise();

    //animate both, the now and next widget to the side, using animation framework
    QPropertyAnimation *animnow = new QPropertyAnimation(widget(now), "pos");

    animnow->setDuration(m_speed);
    animnow->setEasingCurve(m_animationtype);
    animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
    animnow->setEndValue(QPoint(offsetx+pnow.x(), offsety+pnow.y()));
    QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
    animnext->setDuration(m_speed);
    animnext->setEasingCurve(m_animationtype);
    animnext->setStartValue(QPoint(-offsetx+pnext.x(), offsety+pnext.y()));
    animnext->setEndValue(QPoint(pnext.x(), pnext.y()));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

    animgroup->addAnimation(animnow);
    animgroup->addAnimation(animnext);

    QObject::connect(animgroup, SIGNAL(finished()),this,SLOT(animationDoneSlot()));
    m_next=next;
    m_now=now;
    m_active=true;
    animgroup->start();

    //note; the rest is done via a connect from the animation ready;
    //animation->finished() provides a signal when animation is done;
    //so we connect this to some post processing slot,
    //that we implement here below in animationDoneSlot.
}


void SlidingStackedWidget::animationDoneSlot(void) {
    //when ready, call the QStackedWidget slot setCurrentIndex(int)
    setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
    //then hide the outshifted widget now, and  (may be done already implicitely by QStackedWidget)
    widget(m_now)->hide();
    //then set the position of the outshifted widget now back to its original
    widget(m_now)->move(m_pnow);
    //so that the application could also still call the QStackedWidget original functions/slots for changings
    //widget(m_now)->update();
    //setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
    m_active=false;
    emit animationFinished();
}



/* REFERENCES

http://doc.trolltech.com/4.6/animation-overview.html#easing-curves
http://doc.trolltech.com/4.6/qpropertyanimation.html
http://doc.trolltech.com/4.6/qanimationgroup.html

*/




