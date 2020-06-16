//
// Created by cc on 2020/6/15.
//

#include "HttpHelper.h"
#include <QFile>
#include <QApplication>
#include <QEventLoop>
#include "../http/QtHttpRequest.h"

using namespace std;

HttpHelper::HttpHelper() = default;

string HttpHelper::get(const std::string& url) {

    string res;
    auto http = pool.enqueue([&res, url](){
        QtHttpRequest request(url);
        request.addRequestHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36");
        request.startSynchronous();
        res = request.getResponseData();
    });

    http.get();
    return res;
}

void HttpHelper::downloadFile(const std::string& url, const std::string& savePath, const std::function<void(bool)>& callBack) {
    auto http = pool.enqueue([url, savePath, callBack](){
        QtHttpRequest request(url);
        request.addRequestHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36");
        request.startSynchronous();
        auto res = request.getResponseData();
        QFile file(savePath.data());
        if(!res.empty() && file.open(QIODevice::WriteOnly))
        {
            file.write(res.data(), res.size());
            file.close();
            callBack(true);
        } else
            callBack(false);
    });
}