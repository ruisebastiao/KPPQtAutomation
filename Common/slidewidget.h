#ifndef SLIDEWIDGET_H
#define SLIDEWIDGET_H

#include <QWidget>
#include <QGesture>

class  SlideWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SlideWidget(QWidget *parent = 0);
    bool Displayed() const;
    void setDisplayed(bool Displayed);

private:
    bool m_displayed;

signals:

public slots:

protected:
    bool event(QEvent *event);


private:
    bool OnGestureEvent(QGestureEvent* pEvent);
    bool OnSwipeGesture(QSwipeGesture* pSwipe);

};

#endif // SLIDEWIDGET_H
