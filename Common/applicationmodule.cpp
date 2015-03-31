#include "applicationmodule.h"



ApplicationModule::ApplicationModule(QObject *parent) : QObject(parent)
{
    m_Name="New Module";
    module_page=0;
    m_TabButton=0;


}

ApplicationModule::~ApplicationModule()
{
    UnLoadModule();
}

void ApplicationModule::InitializeModule(SlidingStackedWidget *modules_widget, QLayout *tabslayout)
{
    m_moduleswidget=modules_widget;

    m_TabButton= new KPPPushButton(modules_widget->parentWidget());
    m_TabButton->grabGesture(Qt::SwipeGesture);
    m_TabButton->setCheckable(true);
    m_TabButton->setText(m_Name);

    tabslayout->addWidget(m_TabButton);
    module_page = new SlideWidget();
    module_page->setDisplayed(true);
    QVBoxLayout* verticalLayout = new QVBoxLayout(module_page);
    verticalLayout->setSpacing(2);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    module_page->setObjectName(this->m_Name);
    modules_widget->addWidget(module_page);
    m_TabButton->AddSubMenu("Configurações","m_configuracoes");
    m_TabButton->setMenuActivation(KPPPushButton::Gesture);
    connect(m_TabButton,SIGNAL(SubMenuClicked(QObject*)),this,SLOT(MenuActionButtonTriggered(QObject*)));
    connect(m_TabButton,SIGNAL(clicked()),this,SLOT(TabButtonClicked()));
    connect(m_moduleswidget,SIGNAL(currentChanged(int)),this,SLOT(ModulesIndexChanged(int)));
}


QString ApplicationModule::getName() const
{
    return m_Name;
}

void ApplicationModule::setName(const QString &Name)
{
    m_Name = Name;
    if(m_TabButton!=0){
        m_TabButton->setText(m_Name);
    }

}

void ApplicationModule::UnLoadModule()
{
    if(m_TabButton!=0)
        m_TabButton->deleteLater();
    if(module_page!=0){
        connect(m_moduleswidget,SIGNAL(animationFinished()),module_page,SLOT(deleteLater()));
        m_moduleswidget->slideInPrev();
        //m_moduleswidget->removeWidget(module_page);
    }



}

void ApplicationModule::SetActivated(bool activated)
{
    if(m_moduleswidget->indexOf(module_page)!=m_moduleswidget->currentIndex()){
        m_moduleswidget->slideInIdx(m_moduleswidget->indexOf(module_page));
    }
    else{
       m_TabButton->setSelected();
    }

    //m_TabButton->setChecked(activated);
}
QString ApplicationModule::getModuleSettingsPath() const
{
    return m_ModuleSettingsPath;
}

void ApplicationModule::setModuleSettingsPath(const QString &ModuleSettingsPath)
{
    m_ModuleSettingsPath = ModuleSettingsPath;

}

void ApplicationModule::setConfigWindowVisible(bool visible)
{

}


void ApplicationModule::TabButtonClicked()
{
    m_moduleswidget->slideInIdx(m_moduleswidget->indexOf(module_page));

}

void ApplicationModule::ModulesIndexChanged(int moduleindex)
{
    if(m_moduleswidget->indexOf(module_page)==moduleindex){
        m_TabButton->setSelected();
    }
    else
        m_TabButton->setSelected(false);

}

void ApplicationModule::MenuActionButtonTriggered(QObject *sender)
{
    if(sender!=0){
       // QAction *sender_action=(QAction*)sender;
        //if(sender_action!=0){

            if(sender->objectName()=="m_configuracoes"){
                setConfigWindowVisible(true);
            }
       // }
    }
}
