#ifndef VISIONMODULE_H
#define VISIONMODULE_H

#include <applicationmodule.h>
#include "visionwindow.h"


class VisionModule : public ApplicationModule
{
public:
    VisionModule(QObject *parent = 0, QString moduleSettingsLoc="");
    ~VisionModule();
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const VisionModule &module);

    void InitializeModule(SlidingStackedWidget *modules_widget, QLayout *tabslayout);
    QString getModuleSettingsPath() const;
    void setModuleSettingsPath(const QString &getModuleSettingsPath);

    void setConfigWindowVisible(bool visible=true);

    VisionSettings *Settings() const;
    void setSettings(VisionSettings *Settings);

private :
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ApplicationModule);
        //boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);

        //ar & boost::serialization::make_nvp("VisionSettings",settings);

    }
    VisionWindow* m_visionmoduleUI;
    VisionSettings *m_settings;

    void ReloadConfigurations();
};

#endif // VISIONMODULE_H
