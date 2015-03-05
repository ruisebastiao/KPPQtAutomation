/**
  @file
  @author Stefan Frings
*/

#include "actionbar.h"
#include <QIcon>
#include <QFontMetrics>
#include <QFont>
#include <QApplication>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <kppcommon.h>
ActionBar::ActionBar(QWidget *parent) : QWidget(parent) {
    //setStyleSheet(parent->styleSheet());



    // Create layout
    layout=new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setSizeConstraint(QLayout::SetNoConstraint);

    // App Icon and Up Button
    {
        appIcon=new QToolButton(this);
        QIcon myicon=QIcon(":/icons/kppautom");
        appIcon->setIcon(myicon);
        appIcon->setText("Opções");
        appIcon->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);        
        //appIcon->setVisible(false);
        appIcon->setAutoRaise(true);
        appIcon->setFocusPolicy(Qt::NoFocus);
        appIcon->setPopupMode(QToolButton::InstantPopup);


        QMenu* menu=new QMenu(this);
        menu->setStyle(&menuStyle); // needed because the icon size cannot be set by a StyleSheet
        menu->setStyleSheet(
                    "QMenu::item {padding: 1.5em 1.5em 1.5em 1.5em; border: 1px solid transparent;}"
                    "QMenu::item::selected {border-color: black}");

        {
            QAction *act=menu->addAction("      Login");
            act->setObjectName("bt_login");
            QIcon myicon2=QIcon(":/icons/user_lock");
            act->setIcon(myicon2);
            QWidget::connect(act, SIGNAL(triggered()), this, SLOT(MenuActionTriggered()));
        }
        {
            QAction *act=menu->addAction("      Definições");
            act->setObjectName("bt_config");
            QIcon myicon2=QIcon(":/icons/config");
            act->setIcon(myicon2);
            QWidget::connect(act, SIGNAL(triggered()), this, SLOT(MenuActionTriggered()));
        }
        appIcon->setMenu(menu);
        layout->addWidget(appIcon);
        QWidget::connect(appIcon, SIGNAL( clicked()), this, SLOT(appIconClicked()));
    }

    {
//        // View Control Button
//        viewControl=new QToolButton(this);

//        viewControl->setText("Opções");
//        viewControl->setVisible(true);
//        viewControl->setAutoRaise(true);


//        //viewControl->setIcon(myicon);

//        viewControl->setFocusPolicy(Qt::NoFocus);
//        viewControl->setPopupMode(QToolButton::InstantPopup);
//        viewControl->setToolButtonStyle(Qt::ToolButtonIconOnly);
//        viewControl->setStyleSheet("font:bold; height:1.5em;");

//        viewMenu=new QMenu(this);
//        viewMenu->setStyle(&menuStyle); // needed because the icon size cannot be set by a StyleSheet
//        viewMenu->setStyleSheet(
//                    "QMenu::item {padding: 0.3em 1.5em 0.3em 1.5em; border: 1px solid transparent;}"
//                    "QMenu::item::selected {border-color: black}");

//        layout->addWidget(viewControl);

    }



    // Spacer
    layout->addStretch();

    // Action Overflow Button
    overflowButton=new QToolButton(this);
    overflowButton->setIcon(QIcon(":/icons/overflow"));
    overflowButton->setToolTip(tr("more"));
    overflowButton->setAutoRaise(true);
    overflowButton->setFocusPolicy(Qt::NoFocus);
    overflowButton->setPopupMode(QToolButton::InstantPopup);
    layout->addWidget(overflowButton);

    // Action Overflow Menu
    overflowMenu=new QMenu(this);
    overflowMenu->setStyle(&menuStyle); // needed because the icon size cannot be set by a StyleSheet
    overflowMenu->setStyleSheet(
                "QMenu::item {padding: 0.3em 1.5em 0.3em 1.5em; border: 1px solid transparent;}"
                "QMenu::item::selected {border-color: black}");
    overflowButton->setMenu(overflowMenu);


}

ActionBar::~ActionBar() {}

void ActionBar::resizeEvent(QResizeEvent* event) {
    int oldWidth=event->oldSize().width();
    int newWidth=event->size().width();
    //qDebug("resize from %i to %i",oldWidth,newWidth);
    if (oldWidth!=newWidth) {
        adjustContent();
    }
}

void ActionBar::MenuActionTriggered()
{
   QObject* sender=QObject::sender();
   if(sender!=0){
       QAction *sender_action=(QAction*)sender;
       if(sender_action!=0){
           emit ActionMenuClicked(sender_action);
           if(sender_action->objectName()=="bt_login"){

           }
       }
   }
}

void ActionBar::buttonclicked()
{
    QToolButton* sender_objec=dynamic_cast<QToolButton*>(sender());

    if (sender_objec!=0) {
        emit ActionButtonClicked(sender_objec);
    }
}

void ActionBar::paintEvent(QPaintEvent*) {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }

void ActionBar::setTitle(const QString& title, bool showUpButton) {
    viewControl->setText(title);
//    if (showUpButton) {
//        appIcon->setIcon(QIcon(":/icons/app_up"));
//        appIcon->setToolTip(tr("up"));
//        QWidget::connect(appIcon, SIGNAL(triggered(QAction*)), this, SLOT(appIconClicked()));
//    }
//    else {
//        appIcon->setIcon(QIcon(":/icons/app"));
//        appIcon->setToolTip("");
//        QWidget::disconnect(this, SLOT(appIconClicked()));
//    }
    adjustContent();
}

void ActionBar::appIconClicked() {
    //appIcon->menu()->show();
    emit up();
}

void ActionBar::adjustContent() {    
    // Get size of one em (text height in pixels)
    int em=fontMetrics().height();

    // update size of app icon and overflow menu button
    appIcon->setIconSize(QSize(2*em,2*em));
    overflowButton->setIconSize(QSize(2*em,2*em));

    // Check if all action buttons fit into the available space with text beside icon.
    bool needOverflow=false;

    int space;
    if(viewControl!=0)
         space=  width() - appIcon->sizeHint().width() - viewControl->sizeHint().width();
    else
        space=  width() - appIcon->sizeHint().width();

    for (int i=0; i<buttonActions.size(); i++) {
        QAction* action=buttonActions.at(i);
        QToolButton* button=actionButtons.at(i);
        if (action->isVisible()) {
            button->setIconSize(QSize(2*em,2*em));
            button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            space-=button->sizeHint().width();
        }
    }
    if (space<0) {

        if (space<0) {
            // The buttons still don't fit, we need an overflow menu.
            needOverflow=true;
        }
    }

    // Calculate space available to display action buttons
    overflowMenu->clear();
    if (viewControl==0) {
        space=width()-pos().x() - appIcon->sizeHint().width();
    }
    else
        space=width()-pos().x() - appIcon->sizeHint().width() - viewControl->sizeHint().width();
    if (needOverflow) {
        space-=overflowButton->sizeHint().width();
    }

    // Show/Hide action buttons and overflow menu entries
    for (int i=0; i<buttonActions.size(); i++) {
        QAction* action=buttonActions.at(i);
        QToolButton* button=actionButtons.at(i);
        if (action->isVisible()) {
            space-=button->sizeHint().width();
            if (space>=0) {
                // show as button
                button->setDisabled(!buttonActions.at(i)->isEnabled());
                button->show();
            }
            else {
                // show as overflow menu entry
                button->hide();
                overflowMenu->addAction(action);
            }
        }
    }

    // Show/Hide the overflow menu button
    if (needOverflow) {
        overflowButton->show();
    }
    else {
        overflowButton->hide();
    }
}

void ActionBar::addAction(QAction* action) {
    QWidget::addAction(action);
    viewMenu->addAction(action);
    if (!viewMenu->isEmpty()) {
        viewControl->setMenu(viewMenu);
    }
}

void ActionBar::addActions(QList<QAction*> actions) {
    QWidget::addActions(actions);
    for (int i=0; i<actions.size(); i++) {
        addAction(actions.at(i));
    }
}

void ActionBar::removeAction(QAction* action) {
    QWidget::removeAction(action);
    viewMenu->removeAction(action);
    if (viewMenu->isEmpty()) {
        viewControl->setMenu(NULL);
    }
}

void ActionBar::addButton(QAction* action, int position) {
    if (position==-1) {
        position=buttonActions.size();
    }

    buttonActions.insert(position,action);
    QToolButton* button=new QToolButton(this);
    button->setText(action->text());
    button->setToolTip(action->text());
    button->setIcon(action->icon());
    button->setDisabled(!action->isEnabled());
    button->setFocusPolicy(Qt::NoFocus);
    button->setAutoRaise(true);
    connect(button,SIGNAL(triggered(QAction*)),action,SLOT(trigger()));
    connect(button, SIGNAL(clicked()), this, SLOT(buttonclicked()));
    actionButtons.insert(position,button);
    layout->insertWidget(position+3,button);
}

void ActionBar::removeButton(QAction* action) {
    QToolButton* button=NULL;
    for (int i=0; i<buttonActions.size(); i++) {
        if (buttonActions.at(i)==action) {
            button=actionButtons.at(i);
            break;
        }
    }
    if (button) {
        layout->removeWidget(button);
        actionButtons.removeOne(button);
        delete button;
        buttonActions.removeOne(action);
    }
}

