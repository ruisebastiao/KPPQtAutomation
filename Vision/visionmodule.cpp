#include "visionmodule.h"
#include "slidewidget.h"
#include "QVBoxLayout"
#include "QPushButton"
#include <qmessagebox.h>

BOOST_CLASS_EXPORT(VisionModule)

VisionModule::VisionModule(QObject *parent,QString moduleSettingsLoc):
ApplicationModule(parent)
{
    m_settings=0;
}

VisionModule::~VisionModule()
{

}

void VisionModule::InitializeModule(SlidingStackedWidget *modules_widget, QLayout *tabslayout)
{

    ApplicationModule::InitializeModule(modules_widget,tabslayout);

    m_TabButton->setIcon(QIcon(":/icons/camera"));
    m_TabButton->setIconSize(QSize(24,24));
    m_TabButton->setVisible(true);


    ReloadConfigurations();

    if(m_settings!=0)
        m_visionmoduleUI= new VisionWindow(modules_widget,module_page->layout(),m_settings);




}



QString VisionModule::getModuleSettingsPath() const
{
return ApplicationModule::getModuleSettingsPath();
}

void VisionModule::setModuleSettingsPath(const QString &ModuleSettingsPath)
{
    ApplicationModule::setModuleSettingsPath(ModuleSettingsPath);

    ReloadConfigurations();

}

void VisionModule::ReloadConfigurations()
{
    QString path=ApplicationModule::getModuleSettingsPath();
    if(m_settings!=0){
        delete m_settings;
        m_settings=0;
    }
    m_settings=new VisionSettings(this);


    if(QFile(path).exists()==false){

          if (QMessageBox(QMessageBox::Question,"Ficheiro não existente!","Criar um novo?",QMessageBox::Yes|QMessageBox::No).exec()== QMessageBox::Yes) {



               m_settings->Save(path);

               //InitializeModule();
                m_settings->Load();
          } else {

          }
    }
    else
        m_settings->Load(path);
}

