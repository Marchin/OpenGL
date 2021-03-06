#include "../Headers/Model.h"
#include "../Headers/Texture.h"
#include "../Headers/Renderer.h"
#include "../Headers/stb_image.h"

namespace model {
	Model::Model(const char * path) {
		LoadModel(path);
	}

	Model::~Model() {
		for (unsigned int i = 0; i < m_meshes.size(); i++) {
			delete m_meshes[i];
		}
	}

	void Model::Draw(Shader& shader) {
		for (unsigned int i = 0; i < m_meshes.size(); i++) {
			m_meshes[i]->Draw(shader);
		}
	}

	void Model::LoadModel(std::string path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		}
		m_directory = path.substr(0, path.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode * node, const aiScene * scene) {
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(ProcessMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh* Model::ProcessMesh(aiMesh * mesh, const aiScene * scene) {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			vertices.push_back(SetupVertex(mesh, i));
		}
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps
				= LoadMaterialsTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps =
				LoadMaterialsTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		return (new Mesh(vertices, indices, textures));
	}

	Vertex Model::SetupVertex(aiMesh* mesh, unsigned int i) {
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		} else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		return vertex;
	}

	std::vector<Texture> Model::LoadMaterialsTextures(aiMaterial * material, aiTextureType type, std::string typeName) {
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
			bool skip = false;
			aiString str;
			material->GetTexture(type, i, &str);
			for (unsigned int j = 0; j < m_loadedTextures.size(); j++) {
				if (std::strcmp(m_loadedTextures[j].path.data(), str.C_Str()) == 0) {
					textures.push_back(m_loadedTextures[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), m_directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
			}
		}
		return textures;
	}

	unsigned int Model::TextureFromFile(const char* str, std::string directory) {
		std::string texturePath = std::string(str);
		texturePath = directory + '/' + texturePath;
		marchinGL::Texture texture(texturePath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		
		GLCall(glBindTexture(GL_TEXTURE_2D, texture.GetID()));

		return texture.GetID();
	}

}