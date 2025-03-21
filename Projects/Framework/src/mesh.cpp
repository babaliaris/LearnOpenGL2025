#include <FRGL/mesh.h>
#include <FRGL/shader.h>
#include <FRGL/texture.h>
#include <GL/glew.h>
#include <FRGL/glcall.h>

namespace FRGL
{
    Mesh::Mesh(const std::vector<Vertex> &vertices,
            const std::vector<unsigned int> &indices,
            const std::vector<Texture *> &textures):
    m_vao(0), m_vbo(0), m_ebo(0), m_num_of_indices(indices.size()),
    m_textures(textures)
    {   
        //Generate the buffers.
        glCall(glGenVertexArrays(1, &m_vao));
        glCall(glGenBuffers(1, &m_vbo));
        glCall(glGenBuffers(1, &m_ebo));
        
        //Bind VAO.
        glCall(glBindVertexArray(m_vao));

        //Bind VBO and transfer the data.
        glCall(glBindBuffer(GL_VERTEX_ARRAY, m_vbo));
        glCall(glBufferData(GL_VERTEX_ARRAY, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW));

        //Position.
        glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position)));
        glCall(glEnableVertexAttribArray(0));

        //Normal.
        glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, normal)));
        glCall(glEnableVertexAttribArray(1));

        //Uv.
        glCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, uv)));
        glCall(glEnableVertexAttribArray(2));

        //Bind EBO and tranfer the data.
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW));

        //Unbind Everything.
        glCall(glBindVertexArray(0));
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        glCall(glBindBuffer(GL_VERTEX_ARRAY, 0));
    }


    Mesh::~Mesh()
    {
        glCall(glDeleteBuffers(1, &m_vbo));
        glCall(glDeleteBuffers(1, &m_ebo));
        glCall(glDeleteVertexArrays(1, &m_vao));

        //TODO Do the textures
    }


    void Mesh::draw(Shader *shader)
    {
        
    }
}