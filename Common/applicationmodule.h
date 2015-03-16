#ifndef APPLICATIONMODULES_H
#define APPLICATIONMODULES_H

#include <QObject>
#include "BoostDef.h"

class ApplicationModule : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationModule(QObject *parent = 0);
    ~ApplicationModule();

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const ApplicationModule &module);


    virtual QString getName() const;
    virtual void setName(const QString &Name);
private:

    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {

        //ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ResizableItem);
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);

        //ar & boost::serialization::make_nvp("m_ROIRect", m_ROIRect);

    }

     QString m_Name;

signals:

public slots:
};

#endif // APPLICATIONMODULES_H
