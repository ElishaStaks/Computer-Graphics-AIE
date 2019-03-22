#include "Camera.h"

using glm::vec3;
using glm::mat4;

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::setPerspective(const float fieldOfView, const float aspectRatio, const float near, const float far)
{
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, near, far);
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	viewTransform = glm::lookAt(from, to, up);
	worldTransform = glm::inverse(viewTransform);

}

void Camera::setPosition(glm::vec3 position)
{
}

void Camera::rotate(const float angle, const glm::vec3 & axis)
{
	worldTransform = glm::rotate(worldTransform, angle, axis);
	viewTransform = glm::inverse(worldTransform);
}

void Camera::translate(glm::vec3 & position)
{														
	worldTransform[3][0] += position.x;					
	worldTransform[3][1] += position.y;					
	worldTransform[3][2] += position.z;					
	viewTransform = glm::inverse(worldTransform);
}