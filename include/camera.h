#ifndef CAMERA
#define CAMERA
#include <QVector3D>



class Camera {
public:
    Camera(int width, int height, const QVector3D& cameraPos,const QVector3D& target, const QVector3D& up);
    Camera(int WindowWidth, int WindowHeight);


    const QVector3D& GetPos() const
    {
        return m_pos;
    }

    const QVector3D& GetTarget() const
    {
        return m_target;
    }

    const QVector3D& GetUp() const
    {
        return m_up;
    }



private:
    void Init();
    void Update();

    QVector3D m_pos;
    QVector3D m_target;
    QVector3D m_up;

    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

};
#endif // CAMERA

