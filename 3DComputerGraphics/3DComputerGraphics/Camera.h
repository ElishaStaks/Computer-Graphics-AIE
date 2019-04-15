#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	// Camera base class
	Camera();
	~Camera();
	
	virtual void update(float deltaTime, GLFWwindow* window) = 0;
	void setPerspective(const float fieldOfView, const float aspectRatio, const float near, const float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setView(const glm::mat4 &view) { viewTransform = view; }
	void setProjection(const glm::mat4 & projection) { projectionTransform = projection; }
	void rotate(const float angle, const glm::vec3 & axis);
	void translate(glm::vec3 & position);

	glm::mat4 getWorldTransform() { return worldTransform; }
	glm::mat4 getView() { return viewTransform; }
	glm::mat4 getProjection() { return projectionTransform; }
	glm::mat4 getProjectionView() { return projectViewTransform; }


protected:
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectViewTransform;

	// private functions
	void updateProjectionViewTransform() {
		projectViewTransform = projectionTransform * viewTransform;
	}
};