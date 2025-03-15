#pragma once
#include <string>

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

        private:
        unsigned int m_id;
        std::string m_vFilename, m_fFilename;

        unsigned int CreateCompileShader(const char *source, unsigned int type);
        unsigned int CreateLinkProgram(const char *vertexSource, const char *fragSource);
        std::string ReadSourceFromFile(const char *filename);
    };
}