#ifndef APPLICATIONMODULSE_H
#define APPLICATIONMODULES_H

#include <QObject>
#include "qabstractitemmodel.h"
#include <string>
#include <fstream>
#include "Common/kppcommon.h"
#include "qdebug.h"



#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


namespace Modules {

template<class T>
class ModulesList :public QAbstractListModel
{
    //Q_OBJECT
public:
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const ModulesList &sett);

    ModulesList(QObject *parent=0) :
        QAbstractListModel(parent)
    {




    }

    //KPPVisionList<KPPVision> *Projects();

    QString getName() const
    {

        return m_Name;
    }
private:
    QString m_Name;
    QList<T*> m_InnerList;

};
}
namespace boost
{
    namespace serialization
    {



    //---------------------------------------------------------------------------
    /// Saves a QList object to a collection
    template<class Archive, class U >
    inline void save(Archive &ar, const QList< U* > &t, const uint /* file_version */ )
    {

        boost::serialization::stl::save_collection< Archive, QList<U*> >(ar, t);
    }

    //---------------------------------------------------------------------------
    /// Loads a QList object from a collection
    template<class Archive, class U>
    inline void load(Archive &ar, QList<U *> &t, const uint /* file_version */ )
    {

        boost::serialization::stl::load_collection<
                Archive,
                QList<U*>,
                boost::serialization::stl::archive_input_seq<Archive, QList<U*> >,
                boost::serialization::stl::no_reserve_imp< QList<U*> > >(ar, t);

    }
    }
}

#endif // APPLICATIONMODULES_H
