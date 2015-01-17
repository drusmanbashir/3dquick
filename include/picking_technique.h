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

#ifndef PICKING_TECHNIQUE_H
#define	PICKING_TECHNIQUE_H

#include "technique.h"
#include <QOpenGLShaderProgram>
#include "ogldev_math_3d.h"
#include "include/render_callbacks.h"
#include "ogldev_types.h"

class PickingTechnique : public Technique, public IRenderCallbacks
{
public:

    PickingTechnique();

    virtual bool Init();

    void SetWVP(const QMatrix4x4& WVP);

    void SetObjectIndex(GLuint ObjectIndex);
    
    void DrawStartCB(GLuint DrawIndex);
    
    GLuint getProgramId(){return m_shaderProg;};
private:
    GLuint m_textureLocation;
    GLuint m_WVPLocation;
    GLuint m_drawIndexLocation;
    GLuint m_objectIndexLocation;
    QOpenGLShaderProgram program;
};

#endif	/* PICKING_TECHNIQUE_H */

