#include <camera.h>


Camera::Camera(int width, int height, const QVector3D& cameraPos,const QVector3D& target, const QVector3D& up)
{
    m_pos = cameraPos;
    m_windowWidth= width;
    m_windowHeight = height;
    m_target = target;
    m_up = up;
    m_up.normalize();


}
Camera::Camera(int WindowWidth, int WindowHeight){
    m_windowHeight = WindowHeight;
    m_windowWidth = WindowWidth;
    m_pos          = QVector3D(0.0f, 0.0f, 0.0f);
    m_target       = QVector3D(0.0f, 0.0f, 1.0f);
    m_target.normalize();
    m_up           = QVector3D(0.0f, 1.0f, 0.0f);


}
