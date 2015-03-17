#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "kppvision.h"
#include "kpphardware.h"
#include "kppcommon.h"
#include <string>
#include <fstream>
#include "BoostDef.h"
#include "qwidget.h"

#include "serializablelist.h"

using namespace Vision;


class  VisionSettings :public QObject
{
    Q_OBJECT
public:
    explicit VisionSettings(QObject *parent = 0);

    //static VisionSettings *settings;
    static QWidget* mainwidget;
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const VisionSettings &sett);




    KPPHardware *Hardware() const;


    SerializableList<KPPVision> *Projects();




    bool Load(QString location);
    bool Save(QString location);
    bool Load();
    bool Save();



    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version);
private:
    QString m_location;
    KPPHardware *m_hardware;
    SerializableList<KPPVision> *m_Projects;

signals:

public slots:

};





#endif // SETTINGS_H
