#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <opencv2/opencv.hpp>
#include "Core.hpp"
#include "FourierTrans.hpp"
#include "ImgProvider.hpp"
#include "App.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    App a;
    a.show();

    return app.exec();
}
