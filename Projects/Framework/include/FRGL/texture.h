#pragma once
#include <iostream>


namespace FRGL
{
    class Texture
    {
        public:
        Texture(const char *filename);
        ~Texture();

        void Bind(unsigned int unit);
        void Unbind();

        private:
        unsigned int m_id, m_boundUnit;
        int m_width, m_height, m_channels;
        std::string m_filename;

        void LoadTextureFromFile(const char *filename);
    };
}
