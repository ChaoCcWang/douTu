//
// Created by cc on 2020/6/15.
//

#ifndef DOUTU_REQUESTTHREAD_H
#define DOUTU_REQUESTTHREAD_H

#include <QThread>
#include <QQueue>
#include <QWaitCondition>
#include <QMutexLocker>
#include "HttpHelper.h"

class RequestThread : public QThread{
    Q_OBJECT

public:
    explicit RequestThread(QObject* parent = nullptr) ;
    ~RequestThread() override;

public:
    void addRequest(const QString& req);

Q_SIGNALS:
//    void sgSendReq(const QString& );
    void sgGotData(const QVector<QPair<QString, QString>>&);

protected:
    void run() override;

private:
    void httpReq(const QString& url);

private:
    bool             _run{};
    QMutex           _mutex;
    QQueue<QString>  _queue;
    QWaitCondition   _wait;

};


#endif //DOUTU_REQUESTTHREAD_H
