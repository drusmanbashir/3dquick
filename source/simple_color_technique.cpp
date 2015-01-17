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

#include "simple_color_technique.h"
#include "ogldev_util.h"




SimpleColorTechnique::SimpleColorTechnique()
{   
}

bool SimpleColorTechnique::Init()
{
//    if (!Technique::Init()) {
//        return false;
//    }
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple_color_vs.glsl"))
        return false;

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple_color_fs.glsl"))
        return false;

    m_shaderProg = program.programId();

    glBindAttribLocation(m_shaderProg, 0, "Position");
    glBindAttribLocation(m_shaderProg, 1, "TexCoord");


     if (!program.link())
    return false;

    m_WVPLocation = GetUniformLocation("gWVP");
    m_DepthLocation = GetUniformLocation("gDepthSampler");
    m_ColorLocation = GetUniformLocation("gPickingSampler");
    m_TextureLocation = GetUniformLocation("gSampler");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
            m_DepthLocation ==INVALID_UNIFORM_LOCATION ||
            m_ColorLocation == INVALID_UNIFORM_LOCATION ||
            m_TextureLocation ==INVALID_UNIFORM_LOCATION  )

    {

        return false;
    }

    glUniform1i(m_DepthLocation, GL_TEXTURE2);
    glUniform1i(m_ColorLocation, GL_TEXTURE1);
    glUniform1i(m_TextureLocation, GL_TEXTURE0);
    return true;
}

void SimpleColorTechnique::SetWVP(const QMatrix4x4& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP.data());
}

