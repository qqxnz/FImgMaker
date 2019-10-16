#ifndef TRANFORM_H
#define TRANFORM_H

#include <QDir>
#include <QDirIterator>

class Tranform
{
public:
    Tranform();
    bool originPathExist(QString path);
    QStringList searchOriginFile(QString path);
    // 图片缩放
    bool imageScaled(QString originPath,QString savePath,QString fileName,int x);
};

#endif // TRANFORM_H
