#include <QApplication>
#include "DouTu.h"

using namespace std;

//
//int main() {
//    std::string url = "https://www.doutula.com/search?keyword=%E6%B5%B7%E8%B4%BC%E7%8E%8B";
//    QtHttpRequest request(url.data());
//    request.addRequestHeader("User-Agent", "Mozilla/5.0 (Linux; Android 11.0; SM-G900P Build/LRX21T) AppleWebKit/537.37 (KHTML, like Gecko) Chrome/70.0.3538.26 Mobile Safari/537.37");
//    bool isOk = request.startSynchronous();
//    return 0;
//}


int main(int argc, char** argv)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    // high dpi
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication app(argc, argv);
    DouTu w;
    w.show();
    return app.exec();
}
