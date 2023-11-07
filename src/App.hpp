#pragma once

#include "Core.hpp"
#include "FourierTrans.hpp"
#include "Histogram.hpp"
#include "ImgProvider.hpp"
#include "Noise.hpp"
#include "Enhancement.hpp"

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
        setFlags(Qt::FramelessWindowHint | Qt::Window);
    }
public slots:
    void loadImg() {
        QString imgPath = QFileDialog::getOpenFileName();
        if (imgPath != "")
            _imgCore->loadImg(imgPath.toStdString());
    };

    void saveImg() {
        QString savePath = QFileDialog::getSaveFileName(nullptr, QString(), QString(), QString("Image Files (*.png)"));
        if(savePath != "")
            _imgCore->saveImg(savePath.toStdString());
    }

    void swapImg() {
        auto tmpImg = _imgCore->getDstImgMat();
        _imgCore->setDstImgMat(_imgCore->getOriImgMat());
        _imgCore->setOriImgMat(tmpImg);
    }

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

    void gaussianNoise() {
        _imgCore->setDstImgMat(Noise().gaussianNoise(_imgCore->getOriImgMat()));
    }

    void saltPepperNoise() {
        _imgCore->setDstImgMat(Noise().saltPepperNoise(_imgCore->getOriImgMat()));
    }

    void medianFilter() {
        _imgCore->setDstImgMat(Noise().medianFilter(_imgCore->getOriImgMat()));
    }

    void adaptiveMedianFilter() {
        _imgCore->setDstImgMat(Noise().adaptiveMedianFilter(_imgCore->getOriImgMat()));
    }

    void averagingFilter() {
        _imgCore->setDstImgMat(Noise().averagingFilter(_imgCore->getOriImgMat()));
    }

    void nonLocalMeansFilter() {
        _imgCore->setDstImgMat(Noise().nonLocalMeansFilter(_imgCore->getOriImgMat()));
    }

    void gaussianBlur() {
        _imgCore->setDstImgMat(Enhancement().gaussianFilter(_imgCore->getOriImgMat()));
    }

    void unsharpMasking() {
        _imgCore->setDstImgMat(Enhancement().unsharpMasking(_imgCore->getOriImgMat()));
    }

    void laplaceSharpening() {
        _imgCore->setDstImgMat(Enhancement().laplaceSharpening(_imgCore->getOriImgMat()));
    }

    void quitApplication() {
        QCoreApplication::quit();
    }

private:
    Core* _imgCore;
};