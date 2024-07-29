#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProg;

public:
	Shader(const char* v, const char* f);
	void compileShaders(const char* v, const char* f);
	GLuint getShaderProg() { return this->shaderProg; }
};