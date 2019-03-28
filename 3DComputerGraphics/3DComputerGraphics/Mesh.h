#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Mesh
{
public:
	// Constructor sets all variables to 0 ('uninitialised')
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	// Main vertex data
	struct Vertex {
		glm::vec4 position;
		// Represents surface facing direction
		glm::vec4 normal;
		// Stores texture coordinate
		glm::vec2 texCoord;
	};

	// Mesh plane
	void initialiseQuad(unsigned int vertexCount, const Vertex* verticies, unsigned int indexCount, unsigned int* indices);
	virtual void draw();

protected:
	// Stores how many triangles our mesh has
	unsigned int triCount;
	// Vertex Array Object (acts as a sort of wrapper for a mesh)
	unsigned int vao;
	// Vertex Buffer Objects
	unsigned int vbo;
	// Index Buffer Object
	unsigned int ibo;
};