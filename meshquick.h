#ifndef MESHQUICK
#define MESHQUICK
#include <QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QtQuick/QQuickItem>


class MeshRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MeshRenderer();
    ~MeshRenderer();

    void setViewportSize(const QSize &size);
public slots:
    void paint();

private:
    QSize m_viewportSize;
    QOpenGLShaderProgram *m_program;


};

class MeshQuick : public QQuickItem {
    Q_OBJECT


public:
    MeshQuick();
    ~MeshQuick();




public slots:

    void sync();
    void cleanup();

private slots:
    void handleWindowCanged(QQuickWindow* win);

private:

    qreal m_t;
    MeshRenderer* m_renderer;
};



#endif // MESHQUICK

