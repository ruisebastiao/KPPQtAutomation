#ifndef VISIONMODULE_H
#define VISIONMODULE_H

#include <applicationmodule.h>

class VisionModule : public ApplicationModule
{
public:
    VisionModule(QObject *parent = 0);
    ~VisionModule();
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const VisionModule &module);


private :
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ApplicationModule);
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);

        //ar & boost::serialization::make_nvp("m_ROIRect", m_ROIRect);

    }

    QString m_Name;
};

#endif // VISIONMODULE_H
