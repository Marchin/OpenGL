#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"


namespace model {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void Draw(Shader& shader);
		void setupMesh();
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<Texture> m_textures;
		unsigned int VAO;
	private:
		unsigned int VBO, EBO;
		VertexArray m_va;
		VertexBuffer m_vb;
		ElementBuffer m_eb;
	};
}

#endif // !MESH_H
