#ifndef KPPACTIONPUSHBUTTON_H
#define KPPACTIONPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>

class KPPActionPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KPPActionPushButton(QWidget *parent = 0,QMenu *parentMenu=0);
    ~KPPActionPushButton();

signals:

private slots:
    void HideMenu();
    void UpdateSize();
public slots:

private:
    QWidget* m_parent;
    QMenu* m_parentMenu;
    // QWidget interface
public:
    QSize sizeHint() const;
};

#endif // KPPACTIONPUSHBUTTON_H
