#ifndef TECHNIQUE_H
#define TECHNIQUE_H
#include <QList>
#include <QOpenGLFunctions>

class Technique: protected QOpenGLFunctions
{
public:

    Technique();

    virtual ~Technique();

    virtual bool Init();

    void Enable();

protected:


    bool AddShader(GLenum ShaderType, const QString& pFilename);
    bool Finalize();

    GLint GetUniformLocation(const char* pUniformName);

    GLint GetProgramParam(GLint param);

    GLuint m_shaderProg;

private:

    typedef QList <GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};


#endif // TECHNIQUE_H
