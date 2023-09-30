#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
