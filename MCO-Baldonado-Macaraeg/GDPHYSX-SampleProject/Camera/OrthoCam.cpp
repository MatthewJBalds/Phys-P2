#include "OrthoCam.h"

OrthoCamera::OrthoCamera(float window_height, float window_width) : MyCamera() {
	this->window_height = window_height;
	this->window_width = window_width;
}

/* Create Ortho Projection */
void OrthoCamera::createProjection() {
	this->projectionMatrix = glm::ortho(-(this->window_width / 2), //Left
		this->window_width / 2, //Right
		-(this->window_height / 2), //Bottom
		this->window_height / 2, //Top
		-0.1f, //Z-Near
		1000.f); //Z-Far
}

/* Ortho Projection */
void OrthoCamera::setProjection(float left, float right, float bottom, float top) {
	this->projectionMatrix = glm::ortho(-left, //Left
		right, //Right
		-bottom, //Bottom
		top, //Top
		-0.1f, //Z-Near
		100.f); //Z-Far
}

/* Perform Camera */
void OrthoCamera::performCamera(GLuint shaderProg, GLFWwindow* window) {
	this->update(window);
	this->render(shaderProg);
}

/* Update Camera Position */
void OrthoCamera::updateCameraPos(GLFWwindow* window) {
	float radius = 500.f;
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (input->getUp()) {
		angleY += 0.1f;
		if (angleY > glm::radians(89.0f)) angleY = glm::radians(89.0f);
	}
	if (input->getDown()) {
		angleY -= 0.1f;
		if (angleY < glm::radians(-89.0f)) angleY = glm::radians(-89.0f);
	}
	if (input->getLeft()) {
		angleX += 0.1f;
	}
	if (input->getRight())
		angleX -= 0.1f;

	this->cameraPos.x = radius * std::sin(angleX) * std::cos(angleY);
	this->cameraPos.y = radius * std::sin(angleY);
	this->cameraPos.z = radius * std::cos(angleY) * std::cos(angleX);

	this->cameraPositionMatrix = glm::translate(glm::mat4(1.0f), this->cameraPos * -1.f);
	this->Forward = glm::normalize(this->Center - this->cameraPos);
}

/* Update View Matrix */
void OrthoCamera::updateViewMatrix() {
	this->viewMatrix = glm::lookAt(this->cameraPos, this->Center, this->Up);
}

/* Update both Camera Position and View Matrix */
void OrthoCamera::update(GLFWwindow* window) {
	this->updateCameraPos(window);
	this->updateViewMatrix();
}