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

#ifndef SHADOWMAPFBO_H
#define	SHADOWMAPFBO_H

#include <QOpenGLFunctions>
class PickingTexture : protected QOpenGLFunctions
{
public:
    PickingTexture();

    ~PickingTexture();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void EnableWriting();
    
    void DisableWriting();

    
    struct PixelInfo {
        GLubyte ObjectID;
        GLubyte DrawID;
        GLubyte PrimID;
//        GLubyte AlphaID;

        PixelInfo()
        {
            ObjectID = 0;
            DrawID = 0;
            PrimID = 0;
//            AlphaID = 0;
        }
    };


    GLuint getTextureIndex(){return m_pickingTexture;}
    GLuint getDepthIndex(){return m_depthTexture;}
    PixelInfo ReadPixel(unsigned int x, unsigned int y);

private:
    GLuint m_fbo;
    GLuint m_pickingTexture;
    GLuint m_depthTexture;
};

#endif	/* SHADOWMAPFBO_H */

