#include "FlyCamera.h"
#include <GLFW/glfw3.h>

FlyCamera::FlyCamera()
{
	setSpeed(3);
	mouseSpeed = .1f;
}

FlyCamera::~FlyCamera()
{
}


void FlyCamera::update(float deltaTime, GLFWwindow* window)
{
	glm::vec3 position(0.0f, 0.0f, 0.0f);
	glm::vec3 forward = { -this->getView()[0][2], -this->getView()[1][2], -this->getView()[2][2] };
	glm::vec3 up = { this->getView()[0][1], this->getView()[1][1], this->getView()[2][1] };
	glm::vec3 right = { this->getView()[0][0], this->getView()[1][0], this->getView()[2][0] };

	// float speed = 3.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += forward * speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= forward * speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * speed * deltaTime;
	}
	this->translate(position);
	//float mouseSpeed = 0.01f;
	double xPos = 0.0;
	double yPos = 0.0;

	glfwGetCursorPos(window, &xPos, &yPos);

	int width = 0;
	int height = 0;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, (double)width / 2.0, (double)height / 2.0);
	glm::vec2 mouseDir = { ((double)width / 2.0) - xPos, ((double)height / 2.0) - yPos };

	this->rotate(mouseDir.x * mouseSpeed * deltaTime, this->getView() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	this->rotate(mouseDir.y * mouseSpeed * deltaTime, { 1.0f, 0.0f, 0.0f });

	updateProjectionViewTransform();
}