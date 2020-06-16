//
// Created by cc on 2020/6/15.
//

#include "DouTu.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QFile>
#include <QUrl>
#include <QTranslator>
#include <QDebug>
#include <QApplication>
#include "RequestThread.h"
#include "CellWgt.h"

DouTu::DouTu(QWidget *parent)
    : QDialog(parent)
{
    QApplication::setStyle("fusion");
    // window flags
    setWindowFlag(Qt::WindowStaysOnTopHint, true);
    setWindowFlag(Qt::X11BypassWindowManagerHint, true);
    // size
    setFixedSize(550, 515);
    // translate
    {
        int language = QLocale::system().language();
        switch (language)
        {
            case QLocale::Chinese:
            {
                static QTranslator qtGloble;
                qtGloble.load(":/dt/translation/qt_zh_CN.qm");
                qApp->installTranslator(&qtGloble);
                //
                static QTranslator wgtQm;
                wgtQm.load(":/dt/translation/widgets_zh_CN.qm");
                qApp->installTranslator(&wgtQm);
                static QTranslator selfQm;
                selfQm.load(":/dt/translation/douTu.qm");
                qApp->installTranslator(&selfQm);
                break;
            }
            default:
                break;
        }
    }
    //
    setWindowTitle(tr("douTu"));
    // qss
    {
        QFile qssFile(":/dt/conf/app.qss");
        if(qssFile.exists() && qssFile.open(QIODevice::ReadOnly))
            qApp->setStyleSheet(qssFile.readAll());
    }
    // init
    initUi();
}

// ui
void DouTu::initUi() {
    // top search
    auto* searchEdit = new QLineEdit(this);
    searchEdit->setObjectName("SearchEdit");
    searchEdit->setFixedWidth(300);
    searchEdit->setTextMargins(10, 0, 0, 0);
    searchEdit->setPlaceholderText(tr("please input keywords"));
    // main
    _wgt = new QTableWidget(this);
    _wgt->setAutoScroll(false);
    _wgt->setFrameShape(QFrame::NoFrame);
    _wgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _wgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _wgt->horizontalHeader()->setVisible(false);
    _wgt->verticalHeader()->setVisible(false);
    _wgt->setShowGrid(false);
    _wgt->setWindowFlags(Qt::FramelessWindowHint);
    _wgt->setColumnCount(5);
    _wgt->setFocusPolicy(Qt::NoFocus);
    _wgt->setSelectionMode(QAbstractItemView::SingleSelection);
    // layout
    auto* mainLay = new QVBoxLayout(this);
//    mainLay->setMargin(0);
    mainLay->setSpacing(16);
    mainLay->addWidget(searchEdit);
    mainLay->addWidget(_wgt);
    mainLay->setAlignment(searchEdit, Qt::AlignCenter);

    // req
    auto *reqThread = new RequestThread(this);
    reqThread->start();
    reqThread->addRequest("http://www.adoutu.com/picture/list/1");

    // connect
    qRegisterMetaType<QVector<QPair<QString,QString> >>("QVector<QPair<QString,QString>>");
    connect(reqThread, &RequestThread::sgGotData, this, &DouTu::showEmoji);
    connect(searchEdit, &QLineEdit::editingFinished, [searchEdit, reqThread](){
        auto keywords = searchEdit->text();
        QUrl qUrl("http://www.adoutu.com/search?keyword=" + keywords);
        reqThread->addRequest(qUrl.toEncoded());
    });
}

void DouTu::showEmoji(const QVector<QPair<QString, QString>> & data) {

    //
    _wgt->clearContents();
    _wgt->setRowCount(0);
    for(const auto* wgt : _cells)
        delete wgt;
    _cells.clear();
    //
    int row = 0, col = 0;
    for(const auto& it : data)
    {
        if (_wgt->rowCount() != row + 1)
        {
            _wgt->insertRow(row);
            _wgt->setRowHeight(row, width() / 5);
        }

        auto* cellWgt = new CellWgt(it.first, it.second);
        _cells.push_back(cellWgt);
        _wgt->setCellWidget(row, col, cellWgt);
        if (++col == 5)
        {
            col = 0;
            row++;
        }
    }
}
