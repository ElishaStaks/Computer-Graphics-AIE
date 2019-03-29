#include "ComputerGraphicsApp.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Gizmos.h>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

ComputerGraphicsApp::ComputerGraphicsApp()
{
}


ComputerGraphicsApp::~ComputerGraphicsApp()
{
}

bool ComputerGraphicsApp::startUp()
{
	// creates openGL window
	if (glfwInit() == false)
		return false;

	window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr) {
		shutDown();
		return false;
	}

	// set current context
	glfwMakeContextCurrent(window);

	// Terminates the window
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		shutDown();
		return false;
	} // creates openGL window

	// Initialises all our gizmos for 3d grid
	aie::Gizmos::create(10000, 10000, 10000, 10000);
	m_Camera = new FlyCamera();

	// Sets up virtual camera
	m_Camera->setLookAt(glm::vec3(10), glm::vec3(0), { 0, 1, 0 });
	m_Camera->setPerspective(glm::pi<float>() * .25f, 16.f / 9.f, .1f, 1000.f);


	// Load vertex shader from file
	m_shaders.loadShader(aie::eShaderStage::VERTEX, "../bootstrap/shaders/phong.vert");

	// Load fragment shader from file
	m_shaders.loadShader(aie::eShaderStage::FRAGMENT, "../bootstrap/shaders/phong.frag");
	if (m_shaders.link() == false) {
		printf("Shader Error: %s \n", m_shaders.getLastError());
	}

	//if (m_gridTexture.load("../bootstrap/bin/textures/numbered_grid.tga") == false) {
	//	printf("Failed to load texture!\n");
	//	return false;
	//}

	//if (m_spearMesh.load("../bootstrap/models/soulspear/soulspear.obj",true, true) == false) {
	//	printf("Dragon Mesh Error!\n");
	//	return false;
	//}

	//m_spearTransform = {
	//	1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1
	//};

	 //Create simple quad
	m_quadMesh.initialiseQuad();

	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1 
	};


	return true;
 }

void ComputerGraphicsApp::shutDown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	aie::Gizmos::destroy();
}

bool ComputerGraphicsApp::update(float deltaTime)
{
	float time = getTime();
	aie::Gizmos::clear();

	// updates monitor display		
	glfwSwapBuffers(window);		
	glfwPollEvents();
	m_Camera->update(deltaTime, window);

	// rotates light around the scene
	m_light.direction = glm::normalize(vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

	if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE) {
		return false;
	}

	return true;					
}

void ComputerGraphicsApp::draw()
{
	// COLOR_BUFFER_ BIT: wipes the back buffer colours clean
		// DEPTH_BUFFER_BIT: clears the distance to the closest pixels (without this openGL will think the image before is still there)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// colour 
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST); // enables depth buffer

	// Updates in case window resize
	m_Camera->setPerspective(glm::pi<float>() * .25f, 16.f / 9.f, .1f, 1000.f);
	m_shaders.bind();

	aie::Gizmos::addTransform(glm::mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	// Cycles through and adds lines with its matched colour
	for (int i = 0; i < 21; i++)
	{
		aie::Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		aie::Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}
	// Bind shader
	m_shaders.bind();
	// Bind transform
	auto pvm = m_Camera->getProjection() * m_Camera->getView() * m_spearTransform;
	m_shaders.bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting
	m_shaders.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));

	// Bind texture location
	m_shaders.bindUniform("diffuseTexture", 0);

	// Bind texture to specified location
	m_gridTexture.bind(0);

	m_spearMesh.draw();
	//m_quadMesh.draw();

	// Draws the view of the grid
	aie::Gizmos::draw(m_Camera->getProjectionView());
}