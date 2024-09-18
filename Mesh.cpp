#include "Mesh.hpp"
#include <GL/glew.h>	// modern OpenGL aren't present by default
#include <glm/glm.hpp>

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices) 
	: vertices(vertices), indices(indices)
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);
	glGenVertexArrays(1, &vertexArray);

	// Bind
	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	size_t sizeOfVertices = vertices.size() * sizeof(glm::vec3);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	size_t sizeOfIndicess = indices.size() * sizeof(glm::uint32_t);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndicess, indices.data(), GL_STATIC_DRAW);

	// Initialize
	glVertexAttribPointer(0, POINT_SIZE, GL_FLOAT, GL_FALSE, SIZEOF_POINT, nullptr);
	glEnableVertexAttribArray(0);

	// Un-bind, good practice
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Draw() const {
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}