#pragma once

#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QCoreApplication>
#include <QFileDialog>
#include <QQuickItem>
#include <QObject>
#include "Core.hpp"
#include "ImgProvider.hpp"
#include "FourierTrans.hpp"

class App: public QQuickView {
    Q_OBJECT
public:
    App(QWindow *parent = 0): QQuickView(parent), _imgCore(new Core()) {
        engine()->addImageProvider("imgprovider", new ImgProvider(_imgCore));
        setSource(QUrl("qrc:/qml/main.qml"));
        setResizeMode(QQuickView::SizeRootObjectToView);
        rootContext()->setContextProperty("appView", this);
        setFlags(Qt::FramelessWindowHint);
    }
public slots:
    void loadImg() {
        QString imgPath = QFileDialog::getOpenFileName();
        if(imgPath != "")
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

private:
    Core* _imgCore;
};