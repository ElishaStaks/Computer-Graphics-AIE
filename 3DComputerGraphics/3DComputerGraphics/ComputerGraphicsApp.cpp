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
	m_shaders.loadShader(aie::eShaderStage::VERTEX, "../bootstrap/Shaders/simple.vert");

	// Load fragment shader from file
	m_shaders.loadShader(aie::eShaderStage::FRAGMENT, "../bootstrap/Shaders/simple.frag");
	if (m_shaders.link() == false) {
		printf("Shader Error: %s \n", m_shaders.getLastError());
	}

	if (m_dragonMesh.load("../bootstrap/stanford/Dragon.obj") == false) {
		printf("Dragon Mesh Error!\n");
		return false;
	}

	//// load texture
	//texture1.load("myTexture.png");
	//// create a 2x2 black-n-white checker texture
	//// RED simply means one colour channel, i.e. grayscale
	//unsigned char texelData[4] = { 0, 255, 255, 0 };
	//texture2.create(2, 2, aie::Texture::RED, texelData);


	//// Define 6 verticies for 2 triangles
	//Mesh::Vertex vertices[4];
	//vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	//vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	//vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	//vertices[3].position = { 0.5f, 0, -0.5f, 1 };

	//unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
	//m_quadMesh.initialiseQuad(6, vertices, 6, indices);

	//m_quadTransform = {
	//	10, 0, 0, 0,
	//	0, 10, 0, 0,
	//	0, 0, 10, 0,
	//	0, 0, 0, 1 
	//};

	m_dragonTransform = {
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
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
	aie::Gizmos::clear();

	// updates monitor display		
	glfwSwapBuffers(window);		
	glfwPollEvents();
	m_Camera->update(deltaTime, window);

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
	auto pvm = m_Camera->getProjection() * m_Camera->getView() * m_dragonTransform;
	m_shaders.bindUniform("ProjectionViewModel", pvm);

	m_dragonMesh.draw();
	m_quadMesh.draw();

	// Draws the view of the grid
	aie::Gizmos::draw(m_Camera->getProjectionView());
}