//#ifdef __APPLE__
//#include "OpenGL/CGLProfiler.h"
//#include "OpenGL/CGLProfilerFunctionEnum.h"

//GLint myBP = {
//   GLint myBreakpoint[] = { kCGLFEglBindFramebuffer, kCGLProfBreakBefore, 1;}
//   CGLSetOption( kCGLGOEnableBreakpoint, myBreakpoint );

//#endif

#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define INVALID_UNIFORM_LOCATION 0xffffffff
#include <QString>
#include <include/ogldev_util.h>
#include "include/technique.h"
#include <QOpenGLShaderProgram>

Technique::Technique()
{
//    initializeOpenGLFunctions();
    m_shaderProg = 0;
}


Technique::~Technique()
{
    // Delete the intermediate shader objects that have been added to the program
    // The list will only contain something if shaders were compiled but the object itself
    // was destroyed prior to linking.
    for (ShaderObjList::iterator it = m_shaderObjList.begin() ; it != m_shaderObjList.end() ; it++)
    {
        glDeleteShader(*it);
    }

    if (m_shaderProg != 0)
    {
        glDeleteProgram(m_shaderProg);
        m_shaderProg = 0;
    }
}


bool Technique::Init()
{
//    initializeOpenGLFunctions();
//    m_shaderProg = glCreateProgram();

//    if (m_shaderProg == 0) {
//        qDebug()<< "Error creating shader program\n";
//        return false;
//    }

    return true;
}

// Use this method to add shaders to the program. When finished - call finalize()
bool Technique::AddShader(GLenum ShaderType, const QString& pFilename)
{
QString s;

//if (!ReadFile(pFilename, s)) {
//    return false;
//}

GLuint ShaderObj = glCreateShader(ShaderType);

if (ShaderObj == 0) {
    qDebug()
            <<"Error creating shader type "<<ShaderType;
    return false;
}

// Save the shader object - will be deleted in the destructor
m_shaderObjList.push_back(ShaderObj);

const GLchar* p[1];
qDebug()<<s.length();
p[0] = s.toStdString().c_str();
GLint Lengths[1] = { (GLint)s.size() };

glShaderSource(ShaderObj, 1, p, Lengths);

glCompileShader(ShaderObj);

GLint success;
glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
qDebug()<<s;
if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    qDebug()<<"Error compiling "<< pFilename<< InfoLog;
    return false;
}

glAttachShader(m_shaderProg, ShaderObj);

return true;
}


// After all the shaders have been added to the program call this function
// to link and validate the program.
bool Technique::Finalize()
{
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(m_shaderProg);

    glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return false;
    }

    glValidateProgram(m_shaderProg);
    glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        return false;
    }

    // Delete the intermediate shader objects that have been added to the program
    for (ShaderObjList::iterator it = m_shaderObjList.begin() ; it != m_shaderObjList.end() ; it++) {
        glDeleteShader(*it);
    }

    m_shaderObjList.clear();

    return GLCheckError();
}


void Technique::Enable()
{
    glUseProgram(m_shaderProg);
}


GLint Technique::GetUniformLocation(const char* pUniformName)
{
    GLuint Location = glGetUniformLocation(m_shaderProg, pUniformName);

    if (Location == INVALID_UNIFORM_LOCATION) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
    }

    return Location;
}

GLint Technique::GetProgramParam(GLint param)
{
    GLint ret;
    glGetProgramiv(m_shaderProg, param, &ret);
    return ret;
}
