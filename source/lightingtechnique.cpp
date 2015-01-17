#include "lightingtechnique.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QDebug>
#include <QFile>
#include "include/ogldev_util.h"
#include <include/ogldev_math_3d.h>
LightingTechnique::LightingTechnique()
{
}
LightingTechnique::~LightingTechnique(){

}

bool LightingTechnique::Init()
{
    initializeOpenGLFunctions();
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/lighting_vs.glsl"))
        return false;

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/lighting_fs.glsl"))
        return false;



    m_shaderProg = program.programId();
    glBindAttribLocation(m_shaderProg, 0, "Position");
    glBindAttribLocation(m_shaderProg, 1, "TexCoord");
    glBindAttribLocation(m_shaderProg, 2, "Normal");

    if (!Finalize()) {
        return false;
    }

    return true;
}
void LightingTechnique::SetWVP(const QMatrix4x4& WVP)
{
    QMatrix4x4 biasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
    );
    QMatrix4x4 depthBiasMVP = biasMatrix* WVP;
//    program.setUniformValue("gWVP",WVP); //equivalent 'Qt' way
glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, depthBiasMVP.data());
}
void LightingTechnique::SetWorldMatrix(const QMatrix4x4& WorldInverse)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, WorldInverse.data());
}
void LightingTechnique::SetLightWVP(const QMatrix4x4& LightWVP)
{
    glUniformMatrix4fv(m_LightWVPLocation, 1, GL_TRUE, LightWVP.data());
}


void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_samplerLocation, TextureUnit);
}

void LightingTechnique::SetPickingTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_pickingTextureLocation, TextureUnit);
}

void LightingTechnique::SetDepthUnit(unsigned int TextureUnit)
{
    glUniform1i(m_DepthLocation, TextureUnit);
}

void LightingTechnique::SetShadowMapTextureUnit(unsigned int TextureUnit)
{

    glUniform1i(m_shadowMapLocation, TextureUnit);
}




void LightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(m_dirLightLocation.Color, Light.Color.x(), Light.Color.y(), Light.Color.z());
    glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
    QVector3D Direction = Light.Direction;
    Direction.normalize();
    glUniform3f(m_dirLightLocation.Direction, Direction.x(), Direction.y(), Direction.z());
    glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);

}


void LightingTechnique::SetEyeWorldPos(const QVector3D& EyeWorldPos)
{
    glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x(), EyeWorldPos.y(), EyeWorldPos.z());
}
void LightingTechnique::SetMatSpecularIntensity(float Intensity)
{
    glUniform1f(m_matSpecularIntensityLocation, Intensity);
}

void LightingTechnique::SetMatSpecularPower(float Power)
{
    glUniform1f(m_matSpecularPowerLocation, Power);
}

void LightingTechnique::SetDrawId(unsigned int draw)
{
    glUniform1i(m_drawId, draw);
}

void LightingTechnique::SetGoldId(unsigned int draw)
{
    glUseProgram(m_shaderProg);
     glUniform1i(m_shapeGoldId, draw); }




void LightingTechnique::SetPointLights(unsigned int NumLights, const PointLight* pLights)
{
    glUniform1i(m_numPointLightsLocation, NumLights);

    for (unsigned int i = 0 ; i < NumLights ; i++) {
        glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x(), pLights[i].Color.y(), pLights[i].Color.z());
        glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
        glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
        glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x(), pLights[i].Position.y(), pLights[i].Position.z());
        glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
        glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
        glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
    }
}

void LightingTechnique::SetSpotLights(unsigned int NumLights, const SpotLight* pLights)
{
    glUniform1i(m_numSpotLightsLocation, NumLights);

    for (unsigned int i = 0 ; i < NumLights ; i++) {
        glUniform3f(m_spotLightsLocation[i].Color, pLights[i].Color.x(), pLights[i].Color.y(), pLights[i].Color.z());
        glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
        glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
        glUniform3f(m_spotLightsLocation[i].Position,  pLights[i].Position.x(), pLights[i].Position.y(), pLights[i].Position.z());
        QVector3D Direction = pLights[i].Direction;
        Direction.normalize();
        glUniform3f(m_spotLightsLocation[i].Direction, Direction.x(), Direction.y(), Direction.z());
        glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(ToRadian(pLights[i].Cutoff)));
        glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
        glUniform1f(m_spotLightsLocation[i].Atten.Linear,   pLights[i].Attenuation.Linear);
        glUniform1f(m_spotLightsLocation[i].Atten.Exp,      pLights[i].Attenuation.Exp);
    }
}
