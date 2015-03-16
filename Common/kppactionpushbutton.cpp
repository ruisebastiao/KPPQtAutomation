#include "kppactionpushbutton.h"

KPPActionPushButton::KPPActionPushButton(QWidget *parent, QMenu *parentMenu) :
    QPushButton(parent)
{
    m_parent=parent;
    m_parentMenu=parentMenu;
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);


    //connect(parent,SIGNAL())
    connect(parentMenu,SIGNAL(aboutToShow()),this,SLOT(UpdateSize()));
    connect(this,SIGNAL(clicked()),this,SLOT(HideMenu()));
}

KPPActionPushButton::~KPPActionPushButton()
{

}

void KPPActionPushButton::HideMenu()
{
    if(m_parentMenu!=0)
        m_parentMenu->hide();
}

void KPPActionPushButton::UpdateSize()
{

   this->adjustSize();
    m_parentMenu->adjustSize();
    m_parentMenu->close();
    m_parentMenu->show();
 //  m_parentMenu->repaint();
}



QSize KPPActionPushButton::sizeHint() const
{
    QPushButton::sizeHint();
    QSize parentsize=m_parent->size();


    return parentsize;

}
