#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <opencv2/opencv.hpp>
#include "Core.hpp"
#include "FourierTrans.hpp"
#include "ImgProvider.hpp"

int main(int argc, char* argv[]) {
    auto c = Core();
    c.loadImg("C:\\Users\\26354\\Documents\\SEU-DIP-Labwork\\res\\image\\GitHub-Mark.png");
//    cv::Mat processedImg = FourierTrans().fourierTrans(c.getImgMat());
//    cv::imshow("aft", processedImg);
//    cv::waitKey();

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider("imgprovider", new ImgProvider(&c));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
