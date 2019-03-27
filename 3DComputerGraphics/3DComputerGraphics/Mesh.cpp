#include "Mesh.h"
#include "gl_core_4_4.h"


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
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

	// Define 6 verticies for 2 triangles
	Vertex verticies[6];
	verticies[0].position = { -0.5f, 0, 0.5f, 1 };
	verticies[1].position = { 0.5f, 0, 0.5f, 1 };
	verticies[2].position = { -0.5f, 0, -0.5f, 1 };

	verticies[3].position = { -0.5f, 0, -0.5f, 1 };
	verticies[4].position = { 0.5f, 0, 0.5f, 1 };
	verticies[5].position = { -0.5f, 0, -0.5f, 1 };

	// Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), verticies, GL_STATIC_DRAW);

	// Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Unbind buffers
	glBindVertexArray(0);
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
