#include "applicationmodule.h"

ApplicationModule::ApplicationModule(QObject *parent) : QObject(parent)
{
    m_Name="New Module";
}

ApplicationModule::~ApplicationModule()
{

}


QString ApplicationModule::getName() const
{
    return m_Name;
}

void ApplicationModule::setName(const QString &Name)
{
    m_Name = Name;
}
