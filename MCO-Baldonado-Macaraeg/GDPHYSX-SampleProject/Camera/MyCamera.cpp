#include "MyCamera.h"

MyCamera::MyCamera() {
	
}

/* Camera Position */
void MyCamera::createCameraPos() {
	this->cameraPos = glm::vec3(0.f, 0.f, 3.f);
	this->cameraPositionMatrix = glm::translate(glm::mat4(1.0f), this->cameraPos * -1.f);
	this->WorldUp = glm::vec3(0, 1.f, 0);
	this->Center = glm::vec3(0.f, 0.f, 0.f);
	this->Forward = glm::vec3(this->Center - this->cameraPos);
	this->Forward = glm::normalize(this->Forward);
	this->Right = glm::normalize(glm::cross(this->Forward, WorldUp));
	this->Up = glm::normalize(glm::cross(this->Right, this->Forward));
}

/* Camera Orientation */
void MyCamera::createCameraOrientation() {
	this->cameraOrientation = glm::mat4(1.f);

	this->cameraOrientation[0][0] = Right.x;
	this->cameraOrientation[1][0] = Right.y;
	this->cameraOrientation[2][0] = Right.z;

	this->cameraOrientation[0][1] = Up.x;
	this->cameraOrientation[1][1] = Up.y;
	this->cameraOrientation[2][1] = Up.z;

	this->cameraOrientation[0][2] = -Forward.x;
	this->cameraOrientation[1][2] = -Forward.y;
	this->cameraOrientation[2][2] = -Forward.z;
}

/* Camera View */
void MyCamera::createCameraView() {
	this->viewMatrix = cameraOrientation * cameraPositionMatrix;
}

/* Initialize Camera*/
void MyCamera::initializeCamera() {
	this->createProjection();
	this->createCameraPos();
	this->createCameraOrientation();
	this->createCameraView();
}

/* Camera Renderer */
void MyCamera::render(GLuint shaderProg) {
	unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");

	glUniformMatrix4fv(projectionLoc,
		1,
		GL_FALSE,
		glm::value_ptr(this->projectionMatrix));

	unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");

	glUniformMatrix4fv(viewLoc,
		1,
		GL_FALSE,
		glm::value_ptr(this->viewMatrix));
}

void MyCamera::perform(GLuint shaderProg) {
	this->render(shaderProg);
}

glm::vec3 MyCamera::getCameraPos() {
	return this->cameraPos;
}

glm::mat4 MyCamera::getViewMatrix() {
	return this->viewMatrix;
}

glm::mat4 MyCamera::getProjectionMatrix() {
	return this->projectionMatrix;
}
void MyCamera::setCameraPosition(glm::vec3 modelPos) {
	this->cameraPos = modelPos;
}