#pragma once
#include "MyCamera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Renderer/Input.h"

class PerspectiveCamera : public MyCamera {
public:
    PerspectiveCamera(float window_height, float window_width);

public:
    void createProjection();
    void performCamera(GLuint shaderProg, GLFWwindow* window);

private:
    void updateCameraPos(GLFWwindow* window);
    void updateViewMatrix();
    void update(GLFWwindow* window);
};