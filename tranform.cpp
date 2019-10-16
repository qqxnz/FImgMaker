#include "tranform.h"
#include <QDebug>
#include <QImage>
#include <QPainter>


Tranform::Tranform()
{

}


bool Tranform::originPathExist(QString path){
    QDir dir = QDir::current();
    dir.setPath(path);
    if(dir.exists()){
        return true;
    }else{
        return false;
    }
}


QStringList Tranform::searchOriginFile(QString path){
    QStringList result_files;
    QStringList filters;
    filters << "*.png";
    QDir dir = QDir::current();
    dir.setPath(path);
    dir.setNameFilters(filters);//添加过滤器
    QDirIterator iter(dir,QDirIterator::Subdirectories);
    while (iter.hasNext() ){
           iter.next();
           QFileInfo info = iter.fileInfo();
           result_files.append(info.filePath());
    }
    return  result_files;
}

bool Tranform::imageScaled(QString originPath,QString savePath,QString fileName,int x){

    QString originFile = QString("%1/%2").arg(originPath).arg(fileName);
    qDebug() << "原文件" << originFile;
    QImage img = QImage(originFile);
    int width = img.width() / 3 * x;
    int height = img.height() / 3 * x;
    qDebug() << width << "  "<< height;
    QImage newImg = img.scaled(width,height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QString savefile = QString("%1/%2").arg(savePath).arg(fileName);
    qDebug() << "保存文件" << savefile;
    return newImg.save(savefile);

}
