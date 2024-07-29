#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

class Input {
private:
	bool up;
	bool left;
	bool down;
	bool right;
	bool ortho;
	bool perspective;
	bool space;

public:
	Input();
	static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	bool getUp() { return this->up; }
	bool getLeft() { return this->left; }
	bool getDown() { return this->down; }
	bool getRight() { return this->right; }
	bool getOrtho() { return this->ortho; }
	bool getPerspective() { return this->perspective; }
	bool getSpace() { return this->space; }

	void setUp(bool pressed) { this->up = pressed; }
	void setLeft(bool pressed) { this->left = pressed; }
	void setDown(bool pressed) { this->down = pressed; }
	void setRight(bool pressed) { this->right = pressed; }
	void setOrtho(bool pressed) { this->ortho = pressed; }
	void setPerspective(bool pressed) { this->perspective = pressed; }
	void setSpace(bool pressed) { this->space = pressed; }
};
