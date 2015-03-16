#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <string>
#include <fstream>
#include "BoostDef.h"
#include "qwidget.h"
#include "applicationmodule.h"
#include "serializablelist.h"



class  ApplicationSettings :public QObject
{
    Q_OBJECT
    Q_ENUMS(UserLevel)
public:

    enum UserLevel {
        Admin=0,
        Operator=1
    };


    explicit ApplicationSettings(QObject *parent = 0, QString location="");

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const ApplicationSettings &sett);

    static QString loadStyleSheet(const QString &aliasname);

    UserLevel getCurrentUserLevel();
    void setCurrentUserLevel(UserLevel newLevel);


    bool Load(QString location);
    bool Save(QString location);
    bool Load();
    bool Save();

    SerializableList<ApplicationModule>* Modules();

    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version);
private:
    QString m_location;


    SerializableList<ApplicationModule>* m_modules;

    UserLevel CurrentUserLevel;


signals:
    void UserLevelChanged(UserLevel newLevel);

public slots:

};

#endif // APPLICATIONSETTINGS_H
