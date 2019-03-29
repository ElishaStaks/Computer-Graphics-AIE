#include "Application.h"
#include "GLFW/glfw3.h"

eli::Application::Application()
{
}


eli::Application::~Application()
{
}

float eli::Application::getTime() const
{
	return (float)glfwGetTime();
}
