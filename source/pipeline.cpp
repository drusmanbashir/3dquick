#include <pipeline.h>

const QMatrix4x4& Pipeline::GetVPTrans()
{
    QMatrix4x4 CameraTranslationTrans, CameraSetView, PersProjTrans;

    CameraTranslationTrans.translate(-m_camera.Pos.x(), -m_camera.Pos.y(), -m_camera.Pos.z());
    CameraSetView.lookAt(m_camera.Pos,m_camera.Target,m_camera.Up);
    PersProjTrans.perspective(m_persProjInfo.FOV,m_persProjInfo.Aspect,m_persProjInfo.zNear,m_persProjInfo.zFar);

    m_VPtransformation = PersProjTrans * CameraSetView * CameraTranslationTrans;
    return m_VPtransformation;
}

const QMatrix4x4 &Pipeline::GetWorldTrans(){
    QMatrix4x4 ScaleTrans, RotateTrans, TranslationTrans;
    ScaleTrans.scale(m_scale);
    if (m_rotateInfo.isNull())
        RotateTrans.rotate(rotation);
    else
        RotateTrans.rotate(m_degree, m_rotateInfo);
    TranslationTrans.translate(m_worldPos);

    m_Wtransformation = TranslationTrans * RotateTrans * ScaleTrans;
    return m_Wtransformation;


}
const QMatrix4x4& Pipeline::GetWVPTrans()
{
    GetWorldTrans();
    GetVPTrans();

    m_WVPtransformation = m_VPtransformation * m_Wtransformation;
    return m_WVPtransformation;
}

const QMatrix4x4& Pipeline::GetWVTrans()
{
    GetWorldTrans();

    QMatrix4x4 CameraTranslationTrans, CameraSetView;

    CameraTranslationTrans.translate(-m_camera.Pos.x(), -m_camera.Pos.y(), -m_camera.Pos.z());
    CameraSetView.lookAt(m_camera.Pos,m_camera.Target,m_camera.Up);


    m_WVtransformation = CameraSetView * CameraTranslationTrans * m_Wtransformation;
    return m_WVtransformation;
}


void Pipeline::SetRotation(const QQuaternion &rot)
{
    rotation = rot;
}

const QMatrix4x4& Pipeline::GetWPTrans()
{
    QMatrix4x4 PersProjTrans;

    GetWorldTrans();
//	PersProjTrans.InitPersProjTransform(m_persProjInfo);

    PersProjTrans.perspective(m_persProjInfo.FOV,1,m_persProjInfo.zNear,m_persProjInfo.zFar);
    m_WPtransformation = PersProjTrans * m_Wtransformation;
    return m_WPtransformation;
}



