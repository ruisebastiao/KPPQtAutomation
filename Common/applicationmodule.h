#ifndef APPLICATIONMODULES_H
#define APPLICATIONMODULES_H

#include <QObject>
#include "BoostDef.h"
#include "SlidingStackedWidget.h"
#include "qpushbutton.h"
#include "qlayout.h"
#include "kpppushbutton.h"
#include "slidewidget.h"


class ApplicationModule : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationModule(QObject *parent = 0);
    ~ApplicationModule();

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const ApplicationModule &module);

    virtual void InitializeModule(SlidingStackedWidget *modules_widget, QLayout *tabslayout);
    virtual QString getName() const;
    virtual void setName(const QString &Name);
    virtual void UnLoadModule();
    virtual void SetActivated(bool activated=true);


    virtual QString getModuleSettingsPath() const;
    virtual void setModuleSettingsPath(const QString &getModuleSettingsPath);
    virtual void setConfigWindowVisible(bool visible=true);
private:

    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {

        //ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ResizableItem);
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_ModuleSettingsPath),&m_ModuleSettingsPath), file_version);

        //ar & boost::serialization::make_nvp("m_ROIRect", m_ROIRect);

    }
protected:
     SlidingStackedWidget *m_moduleswidget;
     QString m_Name;
     QString m_ModuleSettingsPath;
     KPPPushButton *m_TabButton;
     SlideWidget* module_page;
signals:

private slots:
     void TabButtonClicked();
     void ModulesIndexChanged(int moduleindex);
     void MenuActionButtonTriggered(QObject *sender=0);
public slots:
};

#endif // APPLICATIONMODULES_H
