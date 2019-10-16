#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tranform.h"
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->transformBtn, SIGNAL(clicked()), this, SLOT(tranformBtnClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tranformBtnClicked()
{
    //提示对话框
    if(ui->lineEdit->text().length() < 1){
        int ret1 = QMessageBox::information(this,"提示","输出文件夹不能为空！",QMessageBox::Ok);
        if(ret1 == QMessageBox::Ok){
            qDebug()<<"输出文件夹不能为空!";
        }
        return;
    }

    QString outPutString = ui->lineEdit->text();

    ui->textEdit->setText("开始处理~");
    Tranform *tranFomr = new Tranform();



    QDir originDir(QApplication::applicationDirPath());
    QDir saveDir(QApplication::applicationDirPath());


    originDir.cd("../../../");
    if(!originDir.exists("origin")){
        ui->textEdit->append("origin目录不存在!");
        if(originDir.mkdir("origin")){
            ui->textEdit->append("origin创建成功!");
            ui->textEdit->append("请重操作!");
        }
        return;
    }

    ui->textEdit->append(QString("图片输出目录：%1").arg(outPutString));

    originDir.cd("origin");


    QString assetsFileString = "";

    QStringList list = tranFomr->searchOriginFile(originDir.path());

    if(list.length() < 1){
        QString text = QString("%1 %2 %3").arg("共找到:").arg(list.length()).arg("个需要转换的文件");
        ui->textEdit->append(text);
        return;
    }



    saveDir.cd("../../../");

    if(!saveDir.exists(outPutString)){
        saveDir.mkdir(outPutString);
    }

    saveDir.cd(outPutString);

    if(!saveDir.exists("2.0x")){
        saveDir.mkdir("2.0x");
    }

    if(!saveDir.exists("3.0x")){
        saveDir.mkdir("3.0x");
    }

    QString text = QString("%1 %2 %3").arg("共找到:").arg(list.length()).arg("个需要转换的文件");
    ui->textEdit->append(text);

    for(int i = 0 ; i < list.length();i++){
        QFileInfo info(list[i]);

        QString savePath = QString("%1").arg(saveDir.path());
        tranFomr->imageScaled(info.path(),savePath,info.fileName(),1);
        QFileInfo saveFileInfo(QString("%1/%2").arg(savePath).arg(info.fileName()));
        qDebug() << saveFileInfo;
        if(saveFileInfo.exists()){
            QString text = QString("%1/%2%3").arg(savePath).arg(info.fileName()).arg("保存成功！");
            ui->textEdit->append(text);
            assetsFileString += QString("%1%2/%3\n").arg("    - ").arg(outPutString).arg(info.fileName());
        }else{
            QString text = QString("%1/%2%3").arg(savePath).arg(info.fileName()).arg("保存失败！");
            ui->textEdit->append(text);
        }

    }



    for(int i = 0 ; i < list.length();i++){
        QFileInfo info(list[i]);

        QString savePath = QString("%1%2%3").arg(saveDir.path()).arg("/").arg("2.0x");
        tranFomr->imageScaled(info.path(),savePath,info.fileName(),2);//2倍图
        QFileInfo saveFileInfo(QString("%1/%2").arg(savePath).arg(info.fileName()));
        qDebug() << saveFileInfo;
        if(saveFileInfo.exists()){
            QString text = QString("%1/%2%3").arg(savePath).arg(info.fileName()).arg("保存成功！");
            ui->textEdit->append(text);
            assetsFileString += QString("%1%2/%3%4\n").arg("    - ").arg(outPutString).arg("2.0x/").arg(info.fileName());
        }else{
            QString text = QString("%1/%2%3").arg(savePath).arg(info.fileName()).arg("保存失败！");
            ui->textEdit->append(text);
        }

    }

    for(int i = 0 ; i < list.length();i++){
        QFileInfo info(list[i]);

        QString savePath = QString("%1%2%3").arg(saveDir.path()).arg("/").arg("3.0x");
        tranFomr->imageScaled(info.path(),savePath,info.fileName(),3);//3倍原图
        QFileInfo saveFileInfo(QString("%1/%2").arg(savePath).arg(info.fileName()));
        qDebug() << saveFileInfo;
        if(saveFileInfo.exists()){
            QString text = QString("%1/%2%3").arg(savePath).arg(info.fileName()).arg("保存成功！");
            ui->textEdit->append(text);
            assetsFileString += QString("%1%2/%3%4\n").arg("    - ").arg(outPutString).arg("3.0x/").arg(info.fileName());
        }else{
            QString text = QString("%1/%2%3").arg(savePath).arg(info.fileName()).arg("保存失败！");
            ui->textEdit->append(text);
        }

    }

    qDebug() << "配置文件:"<< assetsFileString << "：配置文件";
    QDir assetsDir(QApplication::applicationDirPath());
    assetsDir.cd("../../../");
    QFile file(QString("%1/%2%3").arg(assetsDir.path()).arg(outPutString).arg("_assets.txt"));
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(assetsFileString.toUtf8());
    file.close();
    ui->textEdit->append("处理完成~");
}

