#pragma once
#include <iostream>


namespace FRGL
{

    enum class TextureType
    {
        NONE, DIFFUSE, SPECULAR
    };

    class Texture
    {
        public:
        Texture(const char *filename);
        ~Texture();

        void Bind(unsigned int unit);
        void Unbind();

        inline void SetType(TextureType type) {m_type = type;}

        inline std::string GetFilename() const {return m_filename;}
        inline TextureType GetType() const {return m_type;}

        private:
        unsigned int m_id, m_boundUnit;
        int m_width, m_height, m_channels;
        std::string m_filename;
        TextureType m_type;

        void LoadTextureFromFile(const char *filename);
    };
}
