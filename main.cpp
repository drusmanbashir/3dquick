#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <meshquick.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    qmlRegisterType<MeshQuick>("OpenGLMesh",1,0,"MeshQ");
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setsource(QUrl("qrc:///main.qml"));
    view.show();

    return a.exec();
}
