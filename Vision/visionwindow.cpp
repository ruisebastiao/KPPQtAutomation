#include "visionwindow.h"
#include "ui_visionwindow.h"

VisionWindow::VisionWindow(QWidget *parent, QLayout *modulelayout,VisionSettings *settings) :
    QFrame(parent),
    m_modulelayout(modulelayout),
    m_visionsettings(settings),
    ui(new Ui::VisionWindow)
{
    ui->setupUi(this);


    ui->treeWidget->AddVisionProjectsModel(settings->Projects());

    //Settings::AppSettings->Projects()->AddItem("asd");


    m_configwindow= new ConfigurationsWidget (this,settings);


    ui->treeWidget->setVisionSettings(settings);

    connect(ui->treeWidget,SIGNAL(ListSelectionChanged(QObject*)),this,SLOT(VisionTreeListSelectionChanged(QObject*)));

    settings->setMainWidget(this);


    foreach (KPPVision *project, settings->Projects()->getList()) {
        foreach (Request *request, project->Requests()->getList()) {
            connect(request->Inspections(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(InspectionInserted(QModelIndex,int,int)));
            foreach (Inspection *inspection, request->Inspections()->getList()) {
                inspection->setView(ui->graphicsView);
            }

        }
    }


//    for(KPPVision *project : Settings::AppSettings->Projects()->getList()) {
//        for(Request *request: project->Requests()->getList()) {
//            connect(request->Inspections(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(InspectionInserted(QModelIndex,int,int)));
//            for(Inspection *inspection: request->Inspections()->getList()) {

//                inspection->setView(ui->graphicsView);

//            }

//        }

//    }

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    QIcon icon;
    icon.addFile(QStringLiteral(":/icons/next"), QSize(), QIcon::Normal, QIcon::Off);
    icon.addFile(QStringLiteral(":/icons/prev"), QSize(), QIcon::Active, QIcon::On);
    ui->bt_toogleSideMenu->setIcon(icon);

    if(m_modulelayout!=0){
        m_modulelayout->addWidget(this);
    }
}

VisionWindow::~VisionWindow()
{
    delete ui;
}

void VisionWindow::toogleModuleSettings()
{
 m_configwindow->ToogleState();
}



void VisionWindow::VisionTreeListSelectionChanged(QObject* newselection){
    if (dynamic_cast<KPPVision*>(newselection)) {

        m_configwindow->setSelectedProject(dynamic_cast<KPPVision*>(newselection));
    }
    else if (dynamic_cast<Request*>(newselection)) {
        m_configwindow->setSelectedRequest(dynamic_cast<Request*>(newselection));
    }
    else if (dynamic_cast<Inspection*>(newselection)) {
        m_configwindow->setSelectedInspection(dynamic_cast<Inspection*>(newselection));
    }
}

void VisionWindow::InspectionInserted(QModelIndex index, int start, int end)
{


    Inspection* insp=index.data(Qt::UserRole).value<Inspection*>();
    if(insp!=0)
        insp->setView(ui->graphicsView);
}

void VisionWindow::on_bt_toogleSideMenu_clicked(bool checked)
{
    if(checked){

        ui->sideWidget->setMenuState(SideWidget::Opened);

    }
    else{
        ui->sideWidget->setMenuState(SideWidget::Closed);
    }
}

void VisionWindow::setConfigwindowVisible(bool visible)
{
    if(visible)
        m_configwindow->show();
    else
        m_configwindow->hide();
}

