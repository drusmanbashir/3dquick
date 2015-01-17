/*
        Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "picking_technique.h"
#include "ogldev_util.h"


PickingTechnique::PickingTechnique()
{   
}

bool PickingTechnique::Init()

{
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/picking_vs.glsl"))
        return false;

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/picking_fs.glsl"))
        return false;
    m_shaderProg = program.programId();

    glBindAttribLocation(m_shaderProg, 0, "Position");
    if (!program.link())
{
    return false;
    }
m_drawIndexLocation = glGetUniformLocation(m_shaderProg,"gDrawIndex");
    return true;
}


void PickingTechnique::SetWVP(const QMatrix4x4& WVP)
{
     glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP.data());
}


void PickingTechnique::DrawStartCB(GLuint DrawIndex)
{
    glUniform1i(m_drawIndexLocation, DrawIndex);
}


void PickingTechnique::SetObjectIndex(GLuint ObjectIndex)
{
//    GLExitIfError;
    glUniform1i(m_objectIndexLocation, ObjectIndex);
//    GLExitIfError;
}
