#pragma once
#include <vector>

namespace FRGL
{
    class Texture;

    struct TextureNode
    {
        TextureNode(Texture *tex):
        m_texture(tex), m_count(0)
        {}

        Texture *m_texture;
        unsigned int m_count;
    };

    class AssetManager
    {
        friend class Application;

        public:
        static Texture *GetTexture(const char *filepath);
        static void ReleaseTexture(Texture *texture);

        private:
        static void Initialize();
        static void Deinitialize();


        protected:
        AssetManager();
        ~AssetManager();

        private:
        static AssetManager *s_this;
        std::vector<TextureNode *> m_textures;
    };
}