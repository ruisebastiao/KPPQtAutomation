#ifndef IMAGEFILECAPTURE_H
#define IMAGEFILECAPTURE_H


#include "capturesource.h"
#include "kpptreepushbutton.h"
#include "BoostDef.h"
#include "kpplineedit.h"

class ImageFileCapture : public CaptureSource
{
    Q_OBJECT
public:
    explicit ImageFileCapture(QObject *parent=0);
    friend class boost::serialization::access;

        template<typename Archive>
    void serialize(Archive & ar, const unsigned int file_version);
private slots:
    void bt_image_loc_clicked();
private:
    KPPRootTreePushButton* bt_imgloc;
    QString m_imagepath;
    KPPLineEdit* edit_img_path;


    // CaptureSource interface
public:
    cv::Mat GetImage();
};



#endif // IMAGEFILECAPTURE_H
