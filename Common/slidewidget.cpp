#include "slidewidget.h"

SlideWidget::SlideWidget(QWidget *parent) :
    QWidget(parent),
    m_displayed(false)
{
   // setAttribute(Qt::WA_AcceptTouchEvents );
   // grabGesture(Qt::SwipeGesture,Qt::ReceivePartialGestures|Qt::IgnoredGesturesPropagateToParent);
}
bool SlideWidget::Displayed() const
{
    return m_displayed;
}

void SlideWidget::setDisplayed(bool displayed)
{
    m_displayed = displayed;
}

bool SlideWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture) {
       return OnGestureEvent(static_cast<QGestureEvent*>(event));

    }

    return QWidget::event(event);
}

bool SlideWidget::OnGestureEvent(QGestureEvent *pEvent)
{
    QGesture *pSwipe = pEvent->gesture(Qt::SwipeGesture);
    if (pSwipe != NULL) {
        OnSwipeGesture(static_cast<QSwipeGesture*>(pSwipe));
    } else {
        qDebug("Unexpected gesture detected. We only grab Qt::SwipeGesture ");

    }
    return true;
}

bool SlideWidget::OnSwipeGesture(QSwipeGesture *pSwipe)
{
    // Do something as result of the gesture
    if (pSwipe->state() == Qt::GestureFinished) {

       return true;
    }
    return false;
}

