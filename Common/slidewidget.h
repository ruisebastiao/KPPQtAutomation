#ifndef SLIDEWIDGET_H
#define SLIDEWIDGET_H

#include <QWidget>

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

};

#endif // SLIDEWIDGET_H
