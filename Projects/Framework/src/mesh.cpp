#include <FRGL/mesh.h>
#include <FRGL/shader.h>
#include <FRGL/texture.h>
#include <GL/glew.h>
#include <FRGL/glcall.h>

namespace FRGL
{
    Mesh::Mesh(const std::vector<Vertex> &vertices,
            const std::vector<unsigned int> &indices,
            const std::vector<Texture *> &textures)
    {
        
    }


    Mesh::~Mesh()
    {
    }


    void Mesh::draw(Shader *shader)
    {

    }
}