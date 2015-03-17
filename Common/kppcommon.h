#ifndef KPPCOMMON_H
#define KPPCOMMON_H

#include "QString"
#include "QMetaEnum"
#include <QObject>

#define ENUM_TO_STRING(c, e, v) \
    (c::staticMetaObject.enumerator(c::staticMetaObject.indexOfEnumerator(#e)).valueToKey(v))

#define STRING_TO_ENUM(c, e, s) \
    (c::e)(c::staticMetaObject.enumerator(c::staticMetaObject.indexOfEnumerator(#e)).keyToValue(s.toUtf8()))


class Common{
public:

    template <class DstType, class SrcType>
    static bool IsType(const SrcType* src);
};

class  QStringSerializable{

public:
    QStringSerializable(QString QStringName, QString *QStringValue);

    QString *getQStringValue() const;
    void setStringValue(QString &value) const;
    std::string getQStringName() const ;

private:
    QString *m_QStringValue;
    QString m_QStringName;
};

#endif // KPPCOMMON_H
