
#include "visionsettings.h"
#include "QApplication"




using namespace Vision;

//VisionSettings* VisionSettings::settings=0;
QWidget* VisionSettings::mainwidget=0;

VisionSettings::VisionSettings(QObject *parent) :
    QObject(parent)
{  

    m_hardware= new KPPHardware(this);
    m_Projects=new SerializableList<KPPVision>(this,"Projects");
}


KPPHardware *VisionSettings::Hardware() const
{
    return m_hardware;
}
SerializableList<KPPVision> *VisionSettings::Projects()
{

    return m_Projects;
}




    template<class Archive>
    void VisionSettings::serialize(Archive & ar, const unsigned int  file_version ){

        ar & boost::serialization::make_nvp("Projects",m_Projects);
        //boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_ProjectsFilePath),&m_ProjectsFilePath), file_version);




    }



bool VisionSettings::Save(QString location){
    // make an archive
    //Settings *settings=this;
        std::ofstream ofs(location.toUtf8().data());
        if(!ofs.good()){

            return false;
        }
        boost::archive::xml_oarchive oa(ofs);
        //oa << BOOST_SERIALIZATION_NVP(settings);
         oa << boost::serialization::make_nvp("Settings", *this);

    return true;
}

bool VisionSettings::Load(){

    return Load(m_location);
}

bool VisionSettings::Save(){

    return Save(m_location);
}


bool VisionSettings::Load(QString location){


    try{
        m_location=location;


        std::ifstream ifs(location.toUtf8().data());
        if(!ifs.good()){

            return false;
        }
        boost::archive::xml_iarchive ia(ifs);

        // restore the schedule from the archive
        //ia >> BOOST_SERIALIZATION_NVP(settings);
         ia >> boost::serialization::make_nvp("Settings", *this);
        //AppSettings=settings;

    }catch(...){
        return false;

    }

    return true;

}
