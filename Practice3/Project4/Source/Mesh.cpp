#include "../Headers/Mesh.h"
#include "../Headers/VertexBufferLayout.h"
#include "../Headers/Renderer.h"

namespace model {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureInfo> textures) 
		: m_vertices(vertices), m_indices(indices), m_texturesInfo(textures),
		m_eb(ElementBuffer(&indices[0], indices.size()) ){

		VertexBufferLayout layout;
		m_va.Bind();
		m_vb.SetData(&m_vertices[0], m_vertices.size() * sizeof(Vertex));;
		m_eb.Bind();
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_va.AddBuffer(m_vb, layout);
		m_va.Unbind();
	}

	Mesh::~Mesh() {
		for (unsigned int i = 0; i < m_texturesInfo.size(); i++) {
			delete m_texturesInfo[i].texture;
		}
	}

	void Mesh::Draw(Shader& shader, marchinGL::TextureController& textureController) const{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int reflectionNr = 1;
		for (unsigned int i = 0; i < m_texturesInfo.size(); i++) {
			std::string number;
			std::string name = m_texturesInfo[i].type;
			if (name == "texture_diffuse") {
				number = std::to_string(diffuseNr++);
			} else if (name == "texture_specular") {
				number = std::to_string(specularNr++);
			} else if (name == "texture_normal") {
				number = std::to_string(normalNr++);
			} else if (name == "texture_reflection") {
				number = std::to_string(reflectionNr++);
			}
			textureController.AddTexture(m_texturesInfo[i].texture, shader, (name + number).c_str());
		}
		m_va.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0));
		m_va.Unbind();
	}
}
//MANTENER CUENTA DE M_COUNT ANTES Y DESPUES