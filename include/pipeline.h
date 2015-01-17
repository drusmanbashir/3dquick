#ifndef PIPELINE
#define PIPELINE
#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
#include <camera.h>
#include <utils.h>


class Pipeline{
public:
    Pipeline(){


    }

    void Scale(const QVector3D& scale)
    {
        m_scale = scale;
    }

    void WorldPos(const QVector3D& Pos)
    {
        m_worldPos = Pos;
    }
    void SetCamera(const QVector3D& Pos, const QVector3D& Target, const QVector3D& Up)
    {
        m_camera.Pos = Pos;
        m_camera.Target = Target;
        m_camera.Up = Up;
    }

    void SetCamera(const Camera& camera)
    {
        SetCamera(camera.GetPos(), camera.GetTarget(), camera.GetUp());
    }
    void SetPerspectiveProj(const PersProjInfo& p)
    {
        m_persProjInfo = p;
    }
    void SetRotAxis(float deg, QVector3D axis){
        m_degree = deg;
        m_rotateInfo = axis;
    }


    void SetRotation(const QQuaternion& rot);
    const QMatrix4x4& GetWPTrans();
    const QMatrix4x4 &GetWVTrans();
    const QMatrix4x4& GetVPTrans();
    const QMatrix4x4& GetWVPTrans();
    const QMatrix4x4& GetWorldTrans();


private:
    QVector3D m_scale;
    QVector3D m_worldPos;
    QQuaternion rotation;
    QVector3D m_rotateInfo;
    float m_degree;
    PersProjInfo m_persProjInfo;

    struct {
        QVector3D Pos;
        QVector3D Target;
        QVector3D Up;
    } m_camera;

    QMatrix4x4 m_WVPtransformation;
    QMatrix4x4 m_VPtransformation;
    QMatrix4x4 m_WPtransformation;
    QMatrix4x4 m_WVtransformation;
    QMatrix4x4 m_Wtransformation;

};



#endif // PIPELINE

