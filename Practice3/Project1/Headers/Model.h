#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Mesh.h"

namespace model {
	class Model {
	public:
		Model(const char* path);
		~Model();
		void Draw(Shader& shader);
	private:
		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
		Vertex SetupVertex(aiMesh * mesh, unsigned int i);
		std::vector<Texture> LoadMaterialsTextures(aiMaterial* material,
			aiTextureType type,
			std::string typeName);
		unsigned int TextureFromFile(const char * str, std::string directory);
		std::vector<Mesh*> m_meshes;
		std::vector<Texture> m_loadedTextures;
		std::string m_directory;
	};
}

#endif // !MODEL_H
