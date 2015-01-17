#ifndef MESHQUICK
#define MESHQUICK
#include <QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QtQuick/QQuickItem>
#include <ubMesh.h>
#include <QBasicTimer>
#include <include/camera.h>
#include <include/utils.h>
#include "include/lightingtechnique.h"
#include <include/pipeline.h>
#include "include/picking_technique.h"
#include "include/picking_texture.h"
#include "include/simple_color_technique.h"
#include <QtGui/QOpenGLFunctions>
//#include "include/picking_technique.h"
//#include "include/picking_technique.h"
//#include "include/simple_color_technique.h"

class MeshRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    MeshRenderer();
    ~MeshRenderer();

    void setViewportSize(const QSize &size) { m_viewportSize = size; }

    void setRotation(QVector2D ax, float angl);

    void initialize();
    void PickingPhase();
    void RenderPhase();

public slots:
    void paint();

private:

    float angle;
    QVector2D axis;

    QSize m_viewportSize;
    float m_fAngle;
    float m_fScale;
    Pipeline p;
    QBasicTimer timer;

 //   Texture *m_pTexture;

    LightingTechnique* m_lightingEffect;
    PickingTechnique *m_pickingEffect;
    Camera* m_pGameCamera;
    DirectionalLight m_directionalLight;
    Mesh* m_pMesh;
    PickingTexture *m_pickingTexture;

    QVector3D m_worldPos[1];

    PersProjInfo m_persProjInfo;


    QVector3D lightPos;
    QVector3D m_scale;
    QVector2D mousePressPosition;
    QVector2D rightMousePosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

    GLuint lightProgID;
    GLuint lightSampler;
    GLuint lightPickingSampler;
    GLuint lightDepthSampler;
    GLuint lightWVP;

    GLuint pickProgID;
    GLuint pickWVP;

};

class MeshQuick : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(QVector2D axis READ axis WRITE setAxis NOTIFY axisChanged)


public:
    MeshQuick();
    void setAngle(float newAngle);
    float angle() ;
    QVector2D axis(){return m_axis;}
    void setAxis(QVector2D newAxis);

signals:
    void angleChanged();
    void axisChanged();

public slots:

    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow* win);

private:

    QVector2D m_axis;
    qreal m_angle;
    MeshRenderer* m_renderer;
};



#endif // MESHQUICK

