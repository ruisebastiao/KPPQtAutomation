#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QsLog.h"
#include "QsLogDest.h"
#include "visionmodule.h"



ApplicationSettings *MainWindow::applicationSettings=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLOG_INFO() << "Loading application settings";
    MainWindow::applicationSettings= new ApplicationSettings();

    applicationSettings->Load();

    connect(applicationSettings->Modules(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(ModuleAdded(QModelIndex , int , int )));

    //applicationSettings->Modules()->AddItem(new VisionModule());

    //applicationSettings->Save();

    connect(MainWindow::applicationSettings,SIGNAL(UserLevelChanged(UserLevel)),this,SLOT(UserLevelChanged(applicationSettings::UserLevel)));
    UserLevelChanged(ApplicationSettings::Admin);

     appsettingsDialog= new ApplicationSettingsDialog(this,applicationSettings);


    //ApplicationSettings->setCurrentUserLevel();

/*    if(QTouchDevice::devices().count()==0){
        QGestureRecognizer* pRecognizer = new SwipeGestureRecognizer();
        grabGesture(QGestureRecognizer::registerRecognizer(pRecognizer));
    }
*/

    ui->actionlayout->setMargin(0);
    ui->actionlayout->setSizeConstraint(QLayout::SetNoConstraint);

    ActionBar* actionBar=new ActionBar(ui->centralWidget);
    //actionBar->setTitle(tr("News"),true);
    //actionBar->addAction(new QAction(tr("Weather"),this));
    //actionBar->addAction(new QAction(tr("Sports"),this));




    actionBar->addButton(new QAction(QIcon(":/icons/settings"),tr("Configurations"),this));
    actionBar->addButton(new QAction(QIcon(":/icons/cancel"),tr("Exit"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/chat"),tr("Chat"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/email"),tr("Email"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/bad"),tr("Bad"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/good"),tr("Good"),this));

    connect(actionBar,SIGNAL(up()),SLOT(bt_Cliked()));
    connect(actionBar,SIGNAL(ActionButtonClicked(QToolButton*)),SLOT(ActionButtonClicked(QToolButton*)));
    connect(actionBar,SIGNAL(ActionMenuClicked(QAction*)),SLOT(MenuActionClicked(QAction*)));

    ui->actionlayout->addWidget(actionBar);   

    if(applicationSettings->Modules()->getList().count()>0){
    for (int var = 0; var < applicationSettings->Modules()->getList().count(); ++var) {
      // QString modulename=applicationSettings->Modules()->getList().at(0)->getName();
       applicationSettings->Modules()->getList().at(var)->InitializeModule(ui->modules_stack,ui->__modules_tab);

    }
     applicationSettings->Modules()->getList().at(0)->SetActivated();
    }
    //ui->modulelayout->addWidget(visionmodule);
    //connect(Settings::AppSettings->Projects(),SIGNAL(Loaded(QObject*)),this,SLOT(LoadDone(QObject*)));


    QLOG_INFO() << "Application initialization done";


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::LoadDone(QObject* Sender){


//    if (dynamic_cast<KPPVisionList<KPPVision>*>(Sender)) {
//        ui->treeWidget->AddVisionProjectsModel(Settings::AppSettings->Projects());
//    }

}

void MainWindow::ModuleAdded(QModelIndex model, int poss, int pose)
{
  ApplicationModule*newmodule= model.data(Qt::UserRole).value<ApplicationModule*>();
  if(newmodule!=0){
    newmodule->InitializeModule(ui->modules_stack,ui->__modules_tab);
  }
}



void MainWindow::ActionButtonClicked(QToolButton *buttonClicked)
{
    if (buttonClicked->text()==tr("Configurations")) {

       // visionmodule->toogleModuleSettings();

    }
    else if (buttonClicked->text()==tr("Exit")) {
        this->close();
    }
}

void MainWindow::MenuActionClicked(QAction *actionmenu)
{
    if (actionmenu->objectName()=="bt_login") {

       // visionmodule->toogleModuleSettings();
       LoginWindow logwindow(this);
       //logwindow.setAttribute(Qt::WA_DeleteOnClose);
       //logwindow= new LoginWindow(this)
       //logwindow.ex;
       if(logwindow.exec()==QDialog::Accepted){
           if (logwindow.getUser()=="Admin") {

           }
       }

    }
    else if (actionmenu->objectName()=="bt_config") {
        appsettingsDialog->exec();

    }

}

void MainWindow::bt_Cliked(){




}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    QMainWindow::mousePressEvent(event);
}



bool MainWindow::IsLineEdit(const QWidget *widget)
{
    return qobject_cast<const QLineEdit*>(widget) != 0;
}



void MainWindow::focusChanged(QWidget *old, QWidget *now)
{
    //    if (IsLineEdit(now) ){
    //        qDebug()<<"Is line edit";
    //    }
}

void MainWindow::UserLevelChanged(ApplicationSettings::UserLevel newlevel)
{
    switch (newlevel) {
    case ApplicationSettings::Admin:
        ui->lbl_user->setText("Utilizador: Administrador");
        break;
    case ApplicationSettings::Operator:
        ui->lbl_user->setText("Utilizador: Operador");
        break;
    default:
        break;
    }
}


