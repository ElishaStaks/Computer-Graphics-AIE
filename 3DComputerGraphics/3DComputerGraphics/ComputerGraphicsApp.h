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

	glm::mat4		         view;
	glm::mat4		         projection;
	GLFWwindow*              window;
	FlyCamera*               m_Camera;

	glm::mat4                m_spearTransform;
	aie::OBJMesh             m_spearMesh;
	Mesh                     m_quadMesh;
	glm::mat4                m_quadTransform;

	aie::Texture             m_gridTexture;
	aie::Texture             texture1;
	aie::Texture             texture2;
	aie::ShaderProgram       m_shaders;
	aie::ShaderProgram       m_shaders2;

	// Light source 1
	struct Light {
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	Light                    m_light;
	glm::vec3                m_ambientLight;

	// Light source 2
	struct Light2 {
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	Light                    m_light2;
	glm::vec3                m_ambientLight2;
};