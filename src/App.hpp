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

    void getHistogram() {
        _imgCore->setDstImgMat(Histogram().getHistogram(_imgCore->getOriImgMat()));
    }

    void customGetHistogram() {
        _imgCore->setDstImgMat(Histogram().customGetHistogram(_imgCore->getOriImgMat()));
    }

    void histogramEqualization() {
        _imgCore->setDstImgMat(Histogram().histogramEqualization(_imgCore->getOriImgMat()));
    }

    void customHistogramEqualization() {
        _imgCore->setDstImgMat(Histogram().customHistogramEqualization(_imgCore->getOriImgMat()));
    }

    void CLAHE() {
        _imgCore->setDstImgMat(Histogram().clahe(_imgCore->getOriImgMat()));
    }

    void customCLAHE() {
        _imgCore->setDstImgMat(Histogram().customClahe(_imgCore->getOriImgMat()));
    }

    void quitApplication() {
        QCoreApplication::quit();
    }

private:
    Core* _imgCore;
};