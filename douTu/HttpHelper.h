//
// Created by cc on 2020/6/15.
//

#ifndef DOUTU_HTTPHELPER_H
#define DOUTU_HTTPHELPER_H


#include <QObject>
#include "ThreadPool.h"

class HttpHelper : public QObject{
public:
    HttpHelper();

public:
    std::string get(const std::string& url);
    void        downloadFile(const std::string& url, const std::string& savePath, const std::function<void(bool)>& callBack);

private:
    ThreadPool pool{};
};


#endif //DOUTU_HTTPHELPER_H
