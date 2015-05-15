#include "request.h"


using namespace Vision;

Request::Request(QObject *parent) :
    QObject(parent)
{
   // this->setObjectName("Request");
    m_Inspections=new SerializableList<Inspection>(this);

    connect(m_Inspections,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(InspectionInserted(QModelIndex,int,int)));

    m_SelectedInspection=0;
}
QGraphicsView *Request::getView() const
{
    return m_view;
}

void Request::setView(QGraphicsView *view)
{
    m_view = view;

    foreach (Inspection *inspection, m_Inspections->getList()) {
        inspection->setView(view);
    }


}

void Request::InspectionInserted(QModelIndex index, int start, int end)
{


    Inspection* insp=index.data(Qt::UserRole).value<Inspection*>();
    if(insp!=0)
        insp->setView(m_view);
}


Vision::Inspection *Request::SelectedInspection() const
{
    return m_SelectedInspection;
}

void Request::setSelectedInspection(Vision::Inspection *SelectedInspection)
{
    m_SelectedInspection = SelectedInspection;
}

SerializableList<Inspection> *Request::Inspections() const
{
    return m_Inspections;
}



QString Request::getName()
{
    return m_Name;
}

void Request::setName(const QString &name)
{
    m_Name=name;
}
