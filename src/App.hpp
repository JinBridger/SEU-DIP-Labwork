#pragma once

#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QCoreApplication>
#include "Core.hpp"
#include "ImgProvider.hpp"

class App: public QQuickView {
    Q_OBJECT
public:
    App(QWindow *parent = 0): QQuickView(parent), _imgCore(new Core()) {
        _imgCore->loadImg("C:\\Users\\26354\\Desktop\\avatar.png");
        engine()->addImageProvider("imgprovider", new ImgProvider(_imgCore));
        setSource(QUrl("qrc:/qml/main.qml"));
        setResizeMode(QQuickView::SizeRootObjectToView);
        rootContext()->setContextProperty("appView", this);
        setFlags(Qt::FramelessWindowHint);
    }
public slots:
    void startMove() {
        this->startSystemMove();
    };

    void startResize(Qt::Edges edges) {
        this->startSystemResize(edges);
    }

    void quitApplication() {
        QCoreApplication::quit();
    }

private:
    Core* _imgCore;
};