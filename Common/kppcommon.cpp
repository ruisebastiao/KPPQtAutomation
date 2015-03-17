#include "kppcommon.h"
#include "qfile.h"
#include "QTextStream.h"



QStringSerializable::QStringSerializable(QString QStringName, QString *QStringValue)
{
    m_QStringValue=QStringValue;
    m_QStringName=QString(QStringName);
}

QString *QStringSerializable::getQStringValue() const
{
    return m_QStringValue;
}

void QStringSerializable::setStringValue(QString &value) const
{
    *m_QStringValue=value;
}

std::string QStringSerializable::getQStringName() const
{

    return m_QStringName.toStdString();



}

template <class DstType, class SrcType>
bool Common::IsType(const SrcType *src)
{
       return dynamic_cast<const DstType*>(src) != 0;
}
