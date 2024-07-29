#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MyCamera {
protected:
	glm::mat4 projectionMatrix;
	glm::vec3 cameraPos;
	glm::mat4 cameraPositionMatrix;
	glm::vec3 WorldUp;
	glm::vec3 Center;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::mat4 cameraOrientation;
	glm::mat4 viewMatrix;
	float window_height;
	float window_width;
	float angleX = 0.f;
	float angleY = 0.f;

public:
	MyCamera();

public:
	virtual void createProjection() = 0;

private:
	void createCameraPos();
	void createCameraOrientation();
	void createCameraView();

public:
	void initializeCamera();
	void render(GLuint shaderProg);
	virtual void perform(GLuint shaderProg);

	glm::vec3 getCameraPos();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void setCameraPosition(glm::vec3 modelPos);
};

