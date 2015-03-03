#ifndef KPPHARDWARE_H
#define KPPHARDWARE_H

#include "QImage"
#include <QObject>
#include "cameras/ids/idscamera.h"




class KPPHardware : public QObject
{
    Q_OBJECT
public:
    explicit KPPHardware(QObject *parent = 0);

    // QList<CameraInfo> *getcamerasInfo() const;


    //IDS::IDSCameraInfo *idsCameraInfo() const;
    //void setIdsCameraInfo(IDSCameraInfo *idsCameraInfo);

private:
    //IDS::IDSCameraInfo* m_idsCameraInfo;
signals:

public slots:


};




#endif // KPPHARDWARE_H
