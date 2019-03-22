#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include <glm/ext.hpp>

class ComputerGraphicsApp : public eli::Application {

public:
	ComputerGraphicsApp();
	virtual ~ComputerGraphicsApp();

	virtual bool startUp();
	virtual void shutDown();
	virtual bool update(float deltaTime);
	virtual void draw();

protected:

	GLFWwindow*     window;
	glm::mat4		view;
	glm::mat4		projection;
	FlyCamera*      m_Camera;
};