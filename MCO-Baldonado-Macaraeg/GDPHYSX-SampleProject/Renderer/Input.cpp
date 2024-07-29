#include "Input.h"

Input::Input() {
    this->up = false;
    this->left = false;
    this->down = false;
    this->right = false;
    this->ortho = false;
    this->perspective = false;
    this->space = false;
}

/* Process Key Inputs */
void Input::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

    if (!input) {
        std::cout << "Failed";
    }

    switch (action) {
    case GLFW_PRESS:
        switch (key) {
        case GLFW_KEY_W:
            input->setUp(true);
            break;

        case GLFW_KEY_A:
            input->setLeft(true);
            break;

        case GLFW_KEY_S:
            input->setDown(true);
            break;

        case GLFW_KEY_D:
            input->setRight(true);
            break;

        case GLFW_KEY_1:
            input->setPerspective(false);
            input->setOrtho(true);
            break;

        case GLFW_KEY_2:
            input->setOrtho(false);
            input->setPerspective(true);
            break;

        case GLFW_KEY_SPACE:
            if (input->getSpace() != true)
                input->setSpace(true);
            else
                input->setSpace(false);
            break;
        }
        break;

    case GLFW_RELEASE:
        switch (key) {
        case GLFW_KEY_W:
            input->setUp(false);
            break;

        case GLFW_KEY_A:
            input->setLeft(false);
            break;

        case GLFW_KEY_S:
            input->setDown(false);
            break;

        case GLFW_KEY_D:
            input->setRight(false);
            break;
        }
        break;
    }
}