#include "applicationsettingsdialog.h"
#include "visionmodule.h"
#include <QMenu>
#include <QWidgetAction>
#include "kppactionpushbutton.h"
#include "qfiledialog.h"
#include "qmessagebox.h"

ApplicationSettingsDialog::ApplicationSettingsDialog(QWidget *parent, ApplicationSettings *appsettings) :
    QDialog(parent),
    m_appsettings(appsettings),
    ui(new Ui::ApplicationSettingsDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint) ;
    if (appsettings!=0) {
        ui->__list_modules->setModel(m_appsettings->Modules());
    }


    ui->__page_modules->setDisplayed(true);
    ui->__page_moduleSettings->setDisplayed(false);


    connect(ui->__list_modules,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(selectionChanged(QItemSelection,QItemSelection)));

   // ui->__bt_addmodule->setPopupMode(QToolButton::InstantPopup);

    QMenu* menu=new QMenu(ui->__bt_addmodule);

    menu->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);


    QWidgetAction *act_visaomodule= new QWidgetAction(menu);


    KPPActionPushButton* addmoduleaction = new KPPActionPushButton(ui->__bt_addmodule,menu);

    addmoduleaction->setText("Modulo de Visão");
    act_visaomodule->setDefaultWidget(addmoduleaction);

     QList<QAction*> *menu_actions= new QList<QAction*>();
     menu_actions->append(act_visaomodule);
     menu->addActions(*menu_actions);

     addmoduleaction->setObjectName("bt_addvisionmodule");


     QWidget::connect(addmoduleaction, SIGNAL(clicked()), this, SLOT(MenuActionButtonTriggered()));


    ui->__bt_addmodule->setMenu(menu);
    ui->__bt_removemodule->setVisible(false);
}

ApplicationSettingsDialog::~ApplicationSettingsDialog()
{
    delete ui;
}

//Ui::ApplicationSettingsDialog *ApplicationSettingsDialog::getUI()
//{
//    return ui;
//}

void ApplicationSettingsDialog::on___bt_exit_clicked()
{
    this->close();
}

void ApplicationSettingsDialog::on___bt_save_clicked()
{
    m_appsettings->Save();
}

void ApplicationSettingsDialog::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList selectedlist= ui->__list_modules->selectionModel()->selectedRows();

    if (selectedlist.count()>0) {
        ApplicationModule* module=selectedlist.at(0).data(Qt::UserRole).value<ApplicationModule*>();
        if(module!=0){
            ui->__bt_removemodule->setVisible(true);
            ui->__lbl_modulename->setText(module->getName());
            ui->__edit_ModuleSettingsPath->setText(module->getModuleSettingsPath());
            ui->__page_moduleSettings->setDisplayed(true);
        }

    }
    else{
        ui->__bt_removemodule->setVisible(false);
        ui->__page_moduleSettings->setDisplayed(false);
    }
}

void ApplicationSettingsDialog::on___bt_removemodule_clicked()
{
    QModelIndexList selectedlist= ui->__list_modules->selectionModel()->selectedRows();
    if (selectedlist.count()>0) {
        m_appsettings->Modules()->removeItem(selectedlist.at(0).data(Qt::UserRole).value<ApplicationModule*>());
    }
}


void ApplicationSettingsDialog::on___bt_addmodule_clicked()
{
    //m_appsettings->Modules()->AddItem()
}

void ApplicationSettingsDialog::MenuActionButtonTriggered()
{
    QObject* sender=QObject::sender();
    if(sender!=0){
       // QAction *sender_action=(QAction*)sender;
        //if(sender_action!=0){

            if(sender->objectName()=="bt_addvisionmodule"){
                m_appsettings->Modules()->AddItem<VisionModule>("New Vision Module");
            }
       // }
    }
}


void ApplicationSettingsDialog::setVisible(bool visible)
{
    if (visible) {
        ui->__stackedsettings->setCurrentIndex(0);
    }

    QDialog::setVisible(visible);

}



void ApplicationSettingsDialog::on___bt_ModuleSettingsPath_clicked()
{
    QModelIndexList selectedlist= ui->__list_modules->selectionModel()->selectedRows();

    if (selectedlist.count()>0) {
        ui->__bt_removemodule->setVisible(true);
        ApplicationModule* module=selectedlist.at(0).data(Qt::UserRole).value<ApplicationModule*>();
        if(module!=0){

            QFileDialog *d=new QFileDialog(0,Qt::Dialog);

            d->setLabelText( QFileDialog::Reject, tr("Cancelar"));
            d->setLabelText( QFileDialog::LookIn, tr("Ver"));
            d->setFileMode(QFileDialog::AnyFile);
            d->setDefaultSuffix("Module");
            d->setNameFilter(tr("Ficheiros Module (*.Module)"));
            if(d->exec()){
                QString path=d->selectedFiles().at(0);
                ui->__edit_ModuleSettingsPath->setText(path);
                module->setModuleSettingsPath(path);

            }
        }


    }





}
