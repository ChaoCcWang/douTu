//
// Created by cc on 2020/6/15.
//

#include <QStandardPaths>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include "CellWgt.h"
#include "HttpHelper.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QMovie>
#include <QDrag>
#include <QMimeData>

CellWgt::CellWgt(const QString& url, const QString& toolTip, QWidget *parent)
    :QFrame(parent)
{
    QByteArray bytePwd = url.toLatin1();
    QByteArray bytePwdMd5 = QCryptographicHash::hash(bytePwd, QCryptographicHash::Md5);
    auto appdata = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto dirPath = QString("%1/%2").arg(appdata, "image");
    auto filePath = QString("%1/%2").arg(dirPath, bytePwdMd5.toHex());
    if(!QFile::exists(dirPath)){
        QDir dir;
        dir.mkpath(dirPath);
    }

    connect(this, &CellWgt::sgSetImage, this, &CellWgt::setCellImage);
    if(!QFile::exists(filePath))
    {
        static HttpHelper helper;
        helper.downloadFile(url.toStdString(), filePath.toStdString(), [this, filePath](bool isOk){
            if(isOk)
                emit sgSetImage(filePath);
        });
    }
    else
        emit sgSetImage(filePath);
    this->setToolTip(toolTip);
}

//
void CellWgt::paintEvent(QPaintEvent *e) {
    const QRectF& rect = this->rect();
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    if(_mov)
    {
        auto pic = _mov->currentImage();
        double width = pic.width(), height = pic.height();
        double maxWidth = rect.width(), maxHeight = rect.height();
        double factor = 1.0;
        double factor1 = maxWidth / width;
        double factor2 = maxHeight / height;
        if (factor1 < 1.0 || factor2 < 1.0) {
            factor = qMin(factor1, factor2);
        }
        width = factor * width - 1;
        height = factor * height - 1;

        painter.drawImage(QRectF{(maxWidth - width) / 2, (maxHeight - height) / 2, width, height}, pic);
    }
    QFrame::paintEvent(e);
}

void CellWgt::setCellImage(const QString& image) {
    _path = image;
    _mov = new QMovie(image);
    _mov->setParent(this);
    _mov->start();
    _mov->setSpeed(80);
    connect(_mov, &QMovie::frameChanged, [this](){
        if(_mov) update();
    });

    update();
}

void CellWgt::mousePressEvent(QMouseEvent *e) {
    _press = true;
    QWidget::mousePressEvent(e);
}

void CellWgt::mouseReleaseEvent(QMouseEvent *e) {
    if(_press)
        _press = false;
    QWidget::mouseReleaseEvent(e);
}

void CellWgt::mouseMoveEvent(QMouseEvent *e) {
    if(_press)
    {
        auto *dg = new QDrag(this);
        auto *md = new QMimeData();
        md->setImageData(QImage(_path));
        dg->setMimeData(md);
        dg->exec();
        dg->deleteLater();
        md->deleteLater();
    }
    QWidget::mouseMoveEvent(e);
}

