#pragma once

#include "Core.hpp"
#include "FourierTrans.hpp"
#include "Histogram.hpp"
#include "ImgProvider.hpp"

#include <QCoreApplication>
#include <QFileDialog>
#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickView>


class App : public QQuickView {
    Q_OBJECT
public:
    App(QWindow* parent = 0) : QQuickView(parent), _imgCore(new Core()) {
        engine()->addImageProvider("imgprovider", new ImgProvider(_imgCore));
        setSource(QUrl("qrc:/qml/main.qml"));
        setResizeMode(QQuickView::SizeRootObjectToView);
        rootContext()->setContextProperty("appView", this);
        setFlags(Qt::FramelessWindowHint);
    }
public slots:
    void loadImg() {
        QString imgPath = QFileDialog::getOpenFileName();
        if (imgPath != "")
            _imgCore->loadImg(imgPath.toStdString());
    };

    void fourierTrans() {
        _imgCore->setDstImgMat(FourierTrans().fourierTrans(_imgCore->getOriImgMat()));
    }

    void customFourierTrans() {
        _imgCore->setDstImgMat(FourierTrans().customFourierTrans(_imgCore->getOriImgMat()));
    }

    void quitApplication() {
        QCoreApplication::quit();
    }

    void test() {
        Histogram().getHistogram(cv::imread("C:/Users/26354/Desktop/avatar.png"));
    }

private:
    Core* _imgCore;
};