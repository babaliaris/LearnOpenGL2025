#include <FRGL/asset_manager.h>
#include <iostream>
#include <FRGL/texture.h>

namespace FRGL
{
    AssetManager *AssetManager::s_this = nullptr;


    void AssetManager::Initialize()
    {
        //Singleton already created.
        if (s_this)
        {
            std::cout << "[AssetManager] Warning! Asset manager already initialized..." << std::endl;
            exit(-1);
            return;
        }

        s_this = new AssetManager();
    }


    void AssetManager::Deinitialize()
    {
        delete s_this;
    }


    Texture *AssetManager::GetTexture(const char *filepath)
    {

        //Search if the texture has already be created.
        for (TextureNode *node : s_this->m_textures)
        {
            if (node->m_texture->GetFilename() == filepath)
            {
                node->m_count++;
                return node->m_texture;
            }
        }

        //Create a new node and a texture and push it to the array.
        Texture *new_texture    = new Texture(filepath);
        TextureNode *new_node   = new TextureNode(new_texture);
        s_this->m_textures.push_back(new_node);

        return new_texture;
    }


    void AssetManager::ReleaseTexture(Texture *texture)
    {
        //Check if the texture is null.
        if (!texture)
        {
            std::cout << "[AssetManager::ReleaseTexture] Warning! Texture is nullprt...";
            return;
        }

        TextureNode *ref_node   = nullptr;
        size_t ref_id           = 0;

        //Search if the texture has already be created.
        for (TextureNode *node : s_this->m_textures)
        {
            if (node->m_texture == texture)
            {
                node->m_count--;
                ref_node = node;
                break;
            }

            ref_id++;
        }

        //Delete the texture and the node.
        if (ref_node->m_count == 0)
        {
            //Delete texture, node and remove it from the vector list.
            delete ref_node->m_texture;
            delete ref_node;
            s_this->m_textures.erase(s_this->m_textures.begin() + ref_id);
        }
    }


    AssetManager::AssetManager()
    {
    }


    AssetManager::~AssetManager()
    {
        //Clean up the textures.
        for (TextureNode *node : s_this->m_textures)
        {
            delete node->m_texture;
            delete node;
        }
    }
}