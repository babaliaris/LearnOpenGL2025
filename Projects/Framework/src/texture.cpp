#include <FRGL/texture.h>
#include <GL/glew.h>
#include <FRGL/glcall.h>
#include <stb_image.h>

namespace FRGL
{
    Texture::Texture(const char *filename):
    m_id(0), m_boundUnit(0), m_width(0), m_height(0),
    m_channels(0), m_filename(filename)
    {
        this->LoadTextureFromFile(filename);
    }


    Texture::~Texture()
    {
        glCall(glDeleteTextures(1, &m_id));
    }


    void Texture::Bind(unsigned int unit)
    {
        m_boundUnit = unit;
        glCall(glActiveTexture(GL_TEXTURE0 + unit));
        glCall(glBindTexture(GL_TEXTURE_2D, m_id));
    }


    void Texture::Unbind()
    {
        glCall(glActiveTexture(GL_TEXTURE0 + m_boundUnit));
        glCall(glBindTexture(GL_TEXTURE_2D, 0));
        glCall(glActiveTexture(GL_TEXTURE0));
    }


    void Texture::LoadTextureFromFile(const char *filename)
    {
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *pixels = stbi_load(filename, &m_width, &m_height, &m_channels, 0);

        if (!pixels)
        {
            std::cout << "[stb_image] Could not load texture: " << m_filename << std::endl;
            return;
        }

        glCall(glGenTextures(1, &m_id));
        glCall(glBindTexture(GL_TEXTURE_2D, m_id));

        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GLint imageFormat;
        switch (m_channels)
        {
            case 2:
                imageFormat = GL_RG;
                break;

            case 3:
                imageFormat = GL_RGB;
                break;

            case 4:
                imageFormat = GL_RGBA;
                break;
            
            default:
                std::cout << "Number of channels are not supported: " << m_channels << std::endl;
                return;
        }

        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, imageFormat, GL_UNSIGNED_BYTE, pixels));

        glCall(glGenerateMipmap(GL_TEXTURE_2D));

        stbi_image_free(pixels);

        glCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
}