#pragma once
#include <string>
#include <glm/glm.hpp>

namespace FRGL
{
    class Shader
    {
        public:
        Shader(const std::string &vSrc, const std::string &fSrc);
        Shader(const char *vFilename, const char *fFilename);
        ~Shader();

        void Bind();
        void UnBind();

        void SetUniform(const char *name, int value);
        void SetUniform(const char *name, float value);
        void SetUniform(const char *name, const glm::vec2 &vec2);
        void SetUniform(const char *name, const glm::vec3 &vec3);
        void SetUniform(const char *name, const glm::vec4 &vec4);
        void SetUniform(const char *name, const glm::mat3 &mat3);
        void SetUniform(const char *name, const glm::mat4 &mat4);

        private:
        unsigned int m_id;
        std::string m_vFilename, m_fFilename, m_programName;

        unsigned int CreateCompileShader(const char *source, unsigned int type);
        unsigned int CreateLinkProgram(const char *vertexSource, const char *fragSource);
        std::string ReadSourceFromFile(const char *filename);
    };
}