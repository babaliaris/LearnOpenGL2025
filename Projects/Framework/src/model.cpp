#include <FRGL/model.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace FRGL
{
    Model::Model(const char *path)
    {
        this->loadModel(path);
    }


    Model::~Model()
    {

    }

    void Model::loadModel(const std::string &path)
    {

    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {

    }

    Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {

    }

    std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                        std::string typeName)
    {

    }
}