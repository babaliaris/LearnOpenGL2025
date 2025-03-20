#pragma once
#include <string>
#include <vector>
#include <assimp/scene.h>

namespace FRGL
{
    class Shader;
    class Mesh;
    class Texture;

    class Model
    {
        public:
        Model(const char *path);
        ~Model();

        void Draw(Shader *shader);

        private:
            std::vector<Mesh *> meshes;
            std::string directory;

            void loadModel(const std::string &path);

            void processNode(aiNode *node, const aiScene *scene);

            Mesh *processMesh(aiMesh *mesh, const aiScene *scene);

            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                                std::string typeName);
    };
}