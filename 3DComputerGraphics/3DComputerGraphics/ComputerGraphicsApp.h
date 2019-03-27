#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include <glm/ext.hpp>
#include "Shader.h"
#include "Mesh.h"

class ComputerGraphicsApp : public eli::Application {

public:
	ComputerGraphicsApp();
	virtual ~ComputerGraphicsApp();

	virtual bool startUp();
	virtual void shutDown();
	virtual bool update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	aie::ShaderProgram       shader;
	Mesh                     m_quadMesh;
	glm::mat4                m_quadTransform;

	GLFWwindow*              window;
	glm::mat4		         view;
	glm::mat4		         projection;
	FlyCamera*               m_Camera;
};