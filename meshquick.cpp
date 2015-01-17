#include<meshquick.h>
#include <string>
#ifdef __APPLE__
std::string phoenixFile = "/Users/usman/Dropbox/code/ogldev-source/content/phoenix_ugv.md2";
std::string cubeFile =  "/Users/usman/Dropbox/code/media/cube.3ds";
std::string spiderFile =  "/Users/usman/Dropbox/code/cube-wc/media/spider.obj";
std::string floorFile = "/Users/usman/Dropbox/code/ogldev-source/content/quad.obj";
std::string suzanneFile = "/Users/usman/Dropbox/code/media/suzanne.3ds";

#else
std::string phoenixFile = "/home/ubashir/Dropbox/code/ogldev-source/content/phoenix_ugv.md2";
std::string spiderFile = "/home/ubashir/Dropbox/code/ogldev-source/content/spider.obj";
std::string cubeFile = "/home/ubashir//Dropbox/code/media/cube.3ds";
std::string floorFile = "/home/ubashir/Dropbox/code/ogldev-source/content/quad.obj";
std::string suzanneFile= "/home/ubashir/Dropbox/code/media/suzanne.3ds";
#endif

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768
#include <QVector3D>
#include <QMouseEvent>
#include <include/camera.h>
#include <math.h>
#include <QDebug>
#include <QImage>
#include <QtQuick/qquickwindow.h>



MeshQuick::MeshQuick(): m_renderer(0)
{

    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}
void MeshQuick::sync()
{
    if (!m_renderer) {
        m_renderer = new MeshRenderer();
        connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()), Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setRotation(m_axis,10);
}

void MeshQuick::cleanup()
{
       if (m_renderer) {
        delete m_renderer;
        m_renderer = 0;
    }

}

void MeshQuick::handleWindowChanged(QQuickWindow *win)
{
        if (win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
//! [1]
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
//! [3]
        win->setClearBeforeRendering(false);
    }

}
float MeshQuick::angle() {
        return m_angle;
    }



void MeshQuick::setAngle(float newAngle)
{
    if (!newAngle == m_angle)
    {
        m_angle = newAngle;
        emit angleChanged();
        if (window())
            window()->update();


    }
}

void MeshQuick::setAxis(QVector2D newAxis){
    if (newAxis != m_axis){

        m_axis.setX(newAxis.x());
        m_axis.setY(newAxis.y());
        emit axisChanged();
        if (window())
            window()->update();
    }
}
MeshRenderer::MeshRenderer(): m_lightingEffect(0),m_pickingEffect(0), m_pickingTexture(0)

{


    m_scale=QVector3D(.1,.1,.1);
    m_fAngle = 0;
    m_fScale = 1;
    m_pGameCamera = NULL;
    m_directionalLight.Color = QVector3D(1.0f, 1.0f, 1.0f);
    m_directionalLight.AmbientIntensity = 1.0f;
    m_directionalLight.DiffuseIntensity = 0.01f;
    m_directionalLight.Direction = QVector3D(1.0f, -1.0, 0.0);
//    m_leftMouseButton.IsPressed = false;
    m_worldPos[0] = QVector3D(-10.0f, 0.0f, 1.0f);
//    m_worldPos[1] = QVector3D(10.0f, 0.0f, 1.0f);

    m_persProjInfo.FOV = 60.0f;
    m_persProjInfo.Height = float(400);
    m_persProjInfo.Width = (float)(400);
    m_persProjInfo.zNear = 1;
    m_persProjInfo.zFar = 100.0f;
    m_persProjInfo.Aspect = qreal(float(400))/qreal(float(400) ? float(400) : 1);


}


void MeshRenderer::initialize(){

    initializeOpenGLFunctions();

    m_lightingEffect = new LightingTechnique();

    if (!m_lightingEffect->Init()) {
    qDebug()<<"Error initializing lighting effect";
    }
    lightProgID = m_lightingEffect->getProgramId();

    lightSampler = glGetUniformLocation(lightProgID, "gSampler");
    lightPickingSampler = glGetUniformLocation(lightProgID, "gPickingSampler");
    lightDepthSampler = glGetUniformLocation(lightProgID, "gDepthSampler");


    lightWVP = glGetUniformLocation(lightProgID, "gWVP");
    m_pMesh = new Mesh();

    if (!m_pMesh->LoadMesh(spiderFile))
{
        qDebug()<<"No Mesh";
//            close();
    }

    glClearColor(1, 0, 0, 1);
//    timer.start(12, this);
}


void MeshRenderer::PickingPhase()
{

    glClearColor(0,1,0,1);
//    p.Scale(QVector3D(.1,.1,.1));
    m_pickingTexture->EnableWriting();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(pickProgID);
    glUniformMatrix4fv(pickWVP,1, GL_FALSE, p.GetWVPTrans().data());
    m_pMesh->Render(m_pickingEffect);

//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebufferObject());
}


void MeshRenderer::RenderPhase()
{

    p.Scale(m_scale);
    p.SetRotation(rotation);
//    p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
    p.SetCamera(QVector3D(0,0,5),QVector3D(0,0,0),QVector3D(0,1,0));
    p.SetPerspectiveProj(m_persProjInfo);

    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(lightProgID);
//    glUseProgram(pickProgID);

//     QMatrix4x4 modelview;
//     modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
//     modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
//     modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
//     modelview.scale(m_fScale);
//     modelview.translate(0.0f, -0.2f, 0.0f);

    glUniformMatrix4fv(lightWVP, 1, GL_FALSE, p.GetWVPTrans().data());
//    glUniformMatrix4fv(lightWVP, 1, GL_FALSE, modelview.data());
//    glUniformMatrix4fv(pickWVP, 1, GL_FALSE, p.GetWVPTrans().data());

    glUniform1i(lightSampler, 0);
    glUniform1i(lightPickingSampler, 1);
    glUniform1i(lightDepthSampler,2);

    m_pMesh->Render(NULL);
//    m_pMesh->Render(m_pickingEffect);
     glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
     m_fAngle +=1.0f;


}


void MeshRenderer::paint()
{
    if (!m_lightingEffect){
        initialize();
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

//    PickingPhase();
    RenderPhase();

}

MeshRenderer::~MeshRenderer(){
    delete m_pMesh;
    delete m_pGameCamera;
    delete m_lightingEffect;
    delete m_pickingEffect;
    delete m_pickingTexture;

}

void MeshRenderer::setRotation(QVector2D ax, float angl)
{
    QVector3D n =QVector3D(ax.y(), ax.x(), 0.0).normalized();

       rotation = QQuaternion::fromAxisAndAngle(n, angl) * rotation;
}
