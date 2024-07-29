#include "PerspectiveCam.h"

PerspectiveCamera::PerspectiveCamera(float window_height, float window_width) : MyCamera() {
    this->window_height = window_height;
    this->window_width = window_width;
    this->cameraPos = glm::vec3(0, 0.f, 500.f);
}

/* Create Perspective Projection */
void PerspectiveCamera::createProjection() {
    this->projectionMatrix = glm::perspective(
        glm::radians(90.f), //FOV
        this->window_height / this->window_width, //Aspect ratio
        0.1f, //ZNear > 0
        1000.f // ZFar
    );
}

void PerspectiveCamera::performCamera(GLuint shaderProg, GLFWwindow* window) {
    this->update(window);
    this->render(shaderProg);
}

/* Update Camera Position */
void PerspectiveCamera::updateCameraPos(GLFWwindow* window) {
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

    this->Forward = glm::normalize(glm::vec3(0, 0, 0) - this->cameraPos);
    this->cameraPositionMatrix = glm::translate(glm::mat4(1.0f), this->cameraPos * -1.f);
}

/* Update View Matrix */
void PerspectiveCamera::updateViewMatrix() {
    this->viewMatrix = glm::lookAt(this->cameraPos, this->cameraPos + this->Forward, this->Up);
}

/* Update both Camera Position and View Matrix */
void PerspectiveCamera::update(GLFWwindow* window) {
    this->updateCameraPos(window);
    this->updateViewMatrix();
}