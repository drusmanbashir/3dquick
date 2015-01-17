#ifndef UBMesh_H
#define UBMesh_H


#include <map>
#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "ogldev_util.h"
#include "ogldev_math_3d.h"
#include "ogldev_texture.h"
#include <QOpenGLFunctions>
#include <include/lightingtechnique.h>
#include <render_callbacks.h>
struct idCheck{
    int objId;
    int drawId;

    idCheck(){
        objId = 999;
        drawId = 999;
    }
};

struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;
    Vector3f m_normal;

    Vertex() {}

    Vertex(const Vector3f& pos, const Vector2f& tex, const Vector3f& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
};


class Mesh: protected QOpenGLFunctions
{
public:
    Mesh();

    ~Mesh();

    bool LoadMesh(const std::string& Filename);

    void Render(IRenderCallbacks* pRenderCallbacks);
    void Render(unsigned int DrawIndex, unsigned int PrimID);
    void setPrimitiveId(int obj, int draw){checksi.objId = obj; checksi.drawId = draw;};

private:
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

    idCheck checksi;
#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry : protected QOpenGLFunctions
    {
        MeshEntry();

        ~MeshEntry();

        void Init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> m_Entries;
    std::vector<Texture*> m_Textures;
};


#endif	/* MESH_H */
