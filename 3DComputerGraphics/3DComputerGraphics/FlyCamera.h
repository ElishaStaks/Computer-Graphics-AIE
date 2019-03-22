#pragma once
#include "Camera.h"
#include "Application.h"

class FlyCamera : public Camera
{
public:
	FlyCamera();
	//FlyCamera(float Speed, float mouseSensitivity);
	~FlyCamera();

	void update(float deltaTime, GLFWwindow* window);
	void setSpeed(float speed) { this->speed = speed; }

protected:
	float speed;
	float mouseSpeed;
};