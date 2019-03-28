#include "Mesh.h"
#include "gl_core_4_4.h"


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad(unsigned int vertexCount, const Vertex* verticies, 
	                      unsigned int indexCount, unsigned int* indices)
{
	// Check that mesh is not initialised
	assert(vao == 0);

	// Generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// Bind vertex array (mesh wrapper)
	glBindVertexArray(vao);
	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), verticies, GL_STATIC_DRAW);

	// Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Bind indicies if there are any
	if (indexCount != 0) {
		glGenBuffers(1, &ibo);


		// bind Vertex buffer 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// Fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else {
		triCount = vertexCount / 3;
	}

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Quad has 2 triangles
	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);

	// Using indicies or just verticies?
	if (ibo != 0) {
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}
