#include "visionmoduletreewidget.h"

#include "qwidget.h"
#include "qdebug.h"
#include "qtimer.h"
#include "qpropertyanimation.h"




VisionModuleTreeWidget::VisionModuleTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{



    //this->clear();
    setRootIsDecorated(true);


    /////Source Name
    item_sourcename=new QTreeWidgetItem;
    item_sourcename->setDisabled(true);

    frame_sourcename=new QFrame();
    frame_sourcename->setAutoFillBackground(false);
    frame_sourcename->setFrameShape(QFrame::NoFrame);


    layout_sourcename= new QVBoxLayout();
    layout_sourcename->setMargin(0);

    bt_sourcename= new KPPRootTreePushButton("Capture Source",item_sourcename);
    bt_sourcename->setMinimumHeight(5);
    layout_sourcename->addWidget(bt_sourcename);
    frame_sourcename->setLayout(layout_sourcename);
    //////////////


    addTopLevelItem(item_sourcename);




//    item_sourcetype=new QTreeWidgetItem();
//    item_sourcename->addChild(item_sourcetype);

//    bt_type= new KPPRootTreePushButton("Capture Type",item_sourcetype);

//    bt_type->setMinimumHeight(5);



//    cb_capturesource=new QComboBox();
//    connect(cb_capturesource,SIGNAL(currentIndexChanged(QString)),this,SLOT(cbCapturecurrentIndexChanged(QString)));




//    item_sourcesettings=new QTreeWidgetItem();



//    item_sourcetype->addChild(item_sourcesettings);
//    //item_type->setChildIndicatorPolicy(QTreeWidgetItem::ChildIndicatorPolicy::DontShowIndicator);

//    //



    setItemWidget(item_sourcename,0,frame_sourcename);
   // setItemWidget(item_sourcetype,0,bt_type);
   // setItemWidget(item_sourcetype,1,cb_capturesource);



 //   item_sourcesettings->setFirstColumnSpanned(true);
  //  item_sourcename->setFirstColumnSpanned(true);

    //cb_capturesource->addItems(CaptureSource::getSourceTypes());

  //  Initialize_Trees();

    //DoHide();
}


void VisionModuleTreeWidget::DoShow(){
    show();
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "maximumWidth");
    //connect(animation1,SIGNAL(finished()),this,SLOT(AnimationFinished()));
    animation1->setDuration(5000);
    animation1->setEasingCurve(QEasingCurve::OutCirc);
    animation1->setStartValue(width());
    animation1->setEndValue(1000);


    animation1->start(QAbstractAnimation::DeleteWhenStopped);
}

void VisionModuleTreeWidget::DoHide(){
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "maximumWidth");
    //connect(animation1,SIGNAL(finished()),this,SLOT(AnimationFinished()));
    animation1->setDuration(1000);
    animation1->setEasingCurve(QEasingCurve::OutCirc);
    animation1->setStartValue(width());
    animation1->setEndValue(0);
    hide();

    animation1->start(QAbstractAnimation::DeleteWhenStopped);
}

void VisionModuleTreeWidget::Initialize_Trees(){



    layout_sourcesettings= new QVBoxLayout();


    //    layout_sourcesettings->addWidget(tree_sourcesettings);
    layout_sourcesettings->setMargin(1);

    frame_sourcesettings=new QFrame();
    frame_sourcesettings->setAutoFillBackground(true);
    frame_sourcesettings->setFrameShape(QFrame::Box);
    frame_sourcesettings->setFrameShadow(QFrame::Raised);
    frame_sourcesettings->setLayout(layout_sourcesettings);
    frame_sourcesettings->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);


    setItemWidget(item_sourcesettings,0,frame_sourcesettings);


}




//void VisionModuleTreeWidget::UpdateSourceType(){

//    if(m_selectedInsp!=0){
//        CaptureSource::CaptureSourceTypes sourcetype=m_selectedInsp->Capture()->getSourceType();

//        if(sourcetype==CaptureSource::CaptureSourceTypes::ImageFile){
//            item_sourcetype->setChildIndicatorPolicy(QTreeWidgetItem::ChildIndicatorPolicy::ShowIndicator);
//        }
//        else{
//            item_sourcetype->setExpanded(false);
//            item_sourcetype->setChildIndicatorPolicy(QTreeWidgetItem::ChildIndicatorPolicy::DontShowIndicator);
//        }

//        if(layout_sourcesettings->count())
//        {
//            QTreeWidget* oldw=qobject_cast<QTreeWidget*>(layout_sourcesettings->itemAt(0)->widget());
//            if(oldw!=0){
//                oldw->setParent(0);
//            }
//        }
//        layout_sourcesettings->addWidget(m_selectedInsp->Capture()->TreeSettings());
//        m_selectedInsp->Capture()->TreeSettings()->show();
//        //m_selectedInsp->Capture()->TreeSettings()->adjustSize();
//        //item_sourcesettings->set

//    }



//    doItemsLayout();
//}





//void VisionModuleTreeWidget::cbCapturecurrentIndexChanged(QString text)
//{
//    if(m_selectedInsp!=0){
//        QString sourcetypename=m_selectedInsp->Capture()->getSourceTypeName();
//        if(sourcetypename!=text){
//            switch (CaptureSource::getSourceTypeFromString(text)) {
//            case CaptureSource::ImageFile:
//                m_selectedInsp->setCapture(new ImageFileCapture());
//                break;
//            case CaptureSource::None:
//                m_selectedInsp->setCapture(new CaptureSource());

//            default:

//                break;
//            }
//            UpdateSourceType();
//        }

//    }
//}





