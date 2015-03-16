#include "applicationsettings.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include "QDir"

ApplicationSettings::ApplicationSettings(QObject *parent,QString location) :
    QObject(parent),
    m_location(location)
{
    if (m_location=="") {
        m_location=QDir(qApp->applicationDirPath()).filePath("app.cfg");
    }

    m_modules= new SerializableList<ApplicationModule>(this,"Modules");
}




ApplicationSettings::UserLevel ApplicationSettings::getCurrentUserLevel()
{
    return CurrentUserLevel;
}

void ApplicationSettings::setCurrentUserLevel(ApplicationSettings::UserLevel newLevel)
{

    if (newLevel!=CurrentUserLevel) {
        emit UserLevelChanged(newLevel);
    }
    CurrentUserLevel=newLevel;
}


QString ApplicationSettings::loadStyleSheet(const QString &aliasname) {
    /* Let's use QFile and point to a resource... */
    QFile data(aliasname);
    //QFile data(":/darkorange");
    QString style;
    /* ...to open the file */
    if(data.open(QFile::ReadOnly)) {
        /* QTextStream... */
        QTextStream styleIn(&data);
        /* ...read file to a string. */
        style = styleIn.readAll();
        data.close();
        /* We'll use qApp macro to get the QApplication pointer
         * and set the style sheet application wide. */
        return style;
    }

    return "";
}




template<class Archive>
void ApplicationSettings::serialize(Archive & ar, const unsigned int  file_version ){

               //ar &   BOOST_SERIALIZATION_NVP(m_Projects);
       // boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_ProjectsFilePath),&m_ProjectsFilePath), file_version);

            ar & boost::serialization::make_nvp("Modules", m_modules);


    }



bool ApplicationSettings::Save(QString location){
    // make an archive
    //Settings *settings=this;
        std::ofstream ofs(location.toUtf8().data());
        if(!ofs.good()){

            return false;
        }
        boost::archive::xml_oarchive oa(ofs);
        //oa << BOOST_SERIALIZATION_NVP(settings);
         oa << boost::serialization::make_nvp("ApplicationSettings", *this);

    return true;
}

bool ApplicationSettings::Load(){

    return Load(m_location);
}

bool ApplicationSettings::Save(){

    return Save(m_location);
}


SerializableList<ApplicationModule> *ApplicationSettings::Modules()
{

    return m_modules;
}


bool ApplicationSettings::Load(QString location){


    try{
        m_location=location;

        if(QFile(location).exists()==false)
            Save(m_location);

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

