//
// Created by cc on 2020/6/15.
//

#include "RequestThread.h"

#include "../gumbo/Document.h"
#include "../gumbo/Node.h"
#include <iostream>
#include <QDebug>


RequestThread::RequestThread(QObject *parent)
    : QThread(parent) {
    _queue.reserve(1000);
//    _manager.moveToThread(this);
//    connect(this, &RequestThread::sgSendReq, this, &RequestThread::httpReq, Qt::QueuedConnection);
}


RequestThread::~RequestThread() {
    _run = false;
    _queue.enqueue("");
//    _wait.wakeAll();
//    _wait.wait(&_mutex);
    wait();
}

void RequestThread::run() {
    _run = true;
    try {
        while (_run)
        {
            QMutexLocker locker(&_mutex);
            _wait.wait(&_mutex, 1000);
            if(_run && !_queue.empty())
            {
                auto req = _queue.last();
                httpReq(req);
//                emit sgSendReq(req);
                _queue.clear();
            }
        }
    }
    catch (const std::exception& e)
    {
        qCritical() << "exception " << e.what();
    }
    catch (...) {
        qCritical() << "exception ";
    }

}

// add req
void RequestThread::addRequest(const QString &req) {
    QMutexLocker locker(&_mutex);
    _queue.enqueue(req);
    _wait.wakeAll();
}

void RequestThread::httpReq(const QString& url) {

    HttpHelper helper;
    auto bytes = helper.get(url.toStdString());
//    qInfo() << bytes.data();
    CDocument doc;
    doc.parse(bytes);

    using namespace std;
    auto res = doc.find("a[class=\"col-sm-3\"]");
    auto img = res.find("img");
    QVector<QPair<QString, QString>> resD;
    for (size_t i = 0; i < qMin(20, (int) img.nodeNum()); i++) {
        resD << QPair<QString, QString>(img.nodeAt(i).attribute("src").data(),
                                        img.nodeAt(i).attribute("title").data());
    }
    if (!resD.empty())
        emit sgGotData(resD);
}
