#include <FRGL/model.h>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <FRGL/mesh.h>
#include <FRGL/texture.h>
#include <FRGL/asset_manager.h>

namespace FRGL
{
    Model::Model(const char *path)
    {
        this->loadModel(path);
    }


    Model::~Model()
    {
        for (Mesh *mesh : m_meshes)
        {
            delete mesh;
        }
    }


    void Model::Draw(Shader *shader)
    {
        for (Mesh *mesh : m_meshes)
        {
            mesh->draw(shader);
        }
    }

    void Model::loadModel(const std::string &path)
    {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode)
        {
            std::cout << "[Model: Error] Could not laod model: " << path << std::endl;
            std::cout << "\t Reason: " << importer.GetErrorString() << std::endl;
            return;
        }

        m_directory = path.substr(0, path.find_last_of("/"));

        this->processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_meshes.push_back( this->processMesh(mesh, scene) );
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            this->processNode(node->mChildren[i], scene);
        }
    }

    Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture *> textures;

        //Get all vertex data.
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            glm::vec3 position(0.0f);
            glm::vec3 normal(0.0f);
            glm::vec2 uv(0.0f);
            
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            if (mesh->mTextureCoords[0])
            {
                uv.s = mesh->mTextureCoords[0][i].x;
                uv.t = mesh->mTextureCoords[0][i].y;
            }

            Vertex vertex(position, normal, uv);

            vertices.push_back(vertex);
        }

        //For each face.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {   
            //For each index.
            for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            {
                indices.push_back(mesh->mFaces[i].mIndices[j]);
            }
        }

        //Load and get the textures.
        if (mesh->mMaterialIndex > 0)
        {
            aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<Texture *> diffuse_maps     = this->loadMaterialTextures(mat, aiTextureType_DIFFUSE);
            std::vector<Texture *> specular_maps    = this->loadMaterialTextures(mat, aiTextureType_SPECULAR);

            textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
            textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

        }

        //Create and add the mesh to the array of meshes.
        return new Mesh(vertices, indices, textures);
    }



    std::vector<Texture *> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
    {
        std::vector<Texture *> textures;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString name;
            mat->GetTexture(type, i, &name);
            
            std::stringstream ss;
            ss << this->m_directory << "/" << name.C_Str();

            Texture *texture = AssetManager::GetTexture(ss.str().c_str());
            texture->SetType(type == aiTextureType_DIFFUSE ? TextureType::DIFFUSE : TextureType::SPECULAR);

            textures.push_back(texture);
        }

        return textures;
    }
}