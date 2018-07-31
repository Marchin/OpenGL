#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"


namespace model {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	struct TextureInfo {
		marchinGL::Texture* texture;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureInfo> textures);
		~Mesh();
		void Draw(Shader& shader);
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<TextureInfo> m_texturesInfo;
		unsigned int VAO;
	private:
		unsigned int VBO, EBO;
		VertexArray m_va;
		VertexBuffer m_vb;
		ElementBuffer m_eb;
	};
}

#endif // !MESH_H
