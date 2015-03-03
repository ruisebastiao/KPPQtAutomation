#ifndef CAMERAINFO_H
#define CAMERAINFO_H

#include "QAbstractListModel"

namespace IDS {



class CameraInfo:public QAbstractListModel
{
    Q_OBJECT

public:
   // virtual operator QString() { return name; }
    //virtual void InitCamera();
    explicit CameraInfo(QObject *parent = 0);
private:
    QString name;


};
}
#endif // CAMERAINFO_H
