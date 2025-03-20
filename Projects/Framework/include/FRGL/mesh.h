#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace FRGL
{
    class Shader;
    class Texture;

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };


    class Mesh
    {
        public:
        Mesh(const std::vector<Vertex> &vertices,
            const std::vector<unsigned int> &indices,
            const std::vector<Texture *> &textures);

        ~Mesh();

        void draw(Shader *shader);

        private:
        unsigned int m_vao, m_vbo, m_ebo;
        std::vector<Texture *> m_textures;
    };
}