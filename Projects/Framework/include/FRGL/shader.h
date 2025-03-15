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
    };
}