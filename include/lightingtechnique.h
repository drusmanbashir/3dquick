#ifndef LIGHTINGTECHNIQUE_H
#define LIGHTINGTECHNIQUE_H

#include "technique.h"
#include <QVector>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

#include "include/render_callbacks.h"
#include <QOpenGLShaderProgram>


struct BaseLight {
    QVector3D Color;
    float AmbientIntensity;
    float DiffuseIntensity;

    BaseLight(){
        AmbientIntensity = 0;
        Color = QVector3D(1,1,1);
        DiffuseIntensity = 0;
    }

};

struct DirectionalLight : public BaseLight
{

    QVector3D Direction;
    DirectionalLight (){

        Direction = QVector3D(0,0,0);

    }

};



struct PointLight: public BaseLight {

    QVector3D Position;
    struct {
        float Constant;
        float Linear;
        float Exp;

    } Attenuation;

    PointLight (){
        Position = QVector3D(0,0,0);
        Attenuation.Constant=1.0;
        Attenuation.Linear = 0;
        Attenuation.Exp = 0;
    }


};

struct SpotLight : public PointLight {
    QVector3D Direction;
    float Cutoff;
    SpotLight (){
        Direction = QVector3D(0,0,0);
        Cutoff = 0;
    }


};


class LightingTechnique : public Technique
{
public:

    static const unsigned int MAX_POINT_LIGHTS = 2;
    static const unsigned int MAX_SPOT_LIGHTS = 2;

    LightingTechnique();
    ~LightingTechnique();
    virtual bool Init();

    void SetLightWVP(const QMatrix4x4& LightWVP);
    void SetShadowMapTextureUnit(unsigned int TextureUnit);

    void SetWVP(const QMatrix4x4& WVP);
    void SetWorldMatrix(const QMatrix4x4& WVP);
    void SetTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionalLight& Light);
    void SetPointLights(unsigned int NumLights, const PointLight* pLights);
    void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
    void SetEyeWorldPos(const QVector3D& EyeWorldPos);
    void SetMatSpecularIntensity(float Intensity);
    void SetMatSpecularPower(float Power);

    void SetDrawId(unsigned int draw);
    GLuint getProgramId(){return m_shaderProg;};

    void SetDepthUnit(unsigned int TextureUnit);

    void SetPickingTextureUnit(unsigned int TextureUnit);
    void SetGoldId(unsigned int draw);
private:

    GLuint m_LightWVPLocation;
    GLuint m_shadowMapLocation;

    GLuint m_WVPLocation;
    GLuint m_WorldMatrixLocation;
    GLuint m_samplerLocation;
    GLuint m_eyeWorldPosLocation;
    GLuint m_matSpecularIntensityLocation;
    GLuint m_matSpecularPowerLocation;
    GLuint m_numPointLightsLocation;
    GLuint m_numSpotLightsLocation;

    GLuint m_pickingTextureLocation;
    GLuint m_shapeGoldId;// this is  a uniform var set by a click
    GLuint m_drawId; // this is set by the Mesh as it goes through each entry;
    GLuint m_DepthLocation;
    QOpenGLShaderProgram program;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } m_dirLightLocation;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;

        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    }m_pointLightsLocation[MAX_POINT_LIGHTS];

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Direction;
        GLuint Cutoff;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_spotLightsLocation[MAX_SPOT_LIGHTS];




};

#endif // LIGHTINGTECHNIQUE_H
