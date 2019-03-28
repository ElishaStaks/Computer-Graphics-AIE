#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include <glm/ext.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Texture.h"

class ComputerGraphicsApp : public eli::Application {

public:
	ComputerGraphicsApp();
	virtual ~ComputerGraphicsApp();

	virtual bool startUp();
	virtual void shutDown();
	virtual bool update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4                m_quadTransform;
	glm::mat4		         view;
	glm::mat4		         projection;
	GLFWwindow*              window;
	FlyCamera*               m_Camera;
	Mesh                     m_quadMesh;
	aie::ShaderProgram       m_shaders;
	glm::mat4                m_dragonTransform;
	aie::OBJMesh             m_dragonMesh;
	aie::Texture             texture1;
	aie::Texture             texture2;
};