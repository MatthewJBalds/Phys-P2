#include "Shader.h"

/* Constructor */
Shader::Shader(const char* v, const char* f) {
	this->compileShaders(v, f);
}

/* Compile shaders */
void Shader::compileShaders(const char* v, const char* f) {
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &v, NULL);
	glCompileShader(this->vertexShader);

	this->fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragShader, 1, &f, NULL);
	glCompileShader(this->fragShader);

	this->shaderProg = glCreateProgram();
	glAttachShader(this->shaderProg, this->vertexShader);
	glAttachShader(this->shaderProg, this->fragShader);

	glLinkProgram(this->shaderProg);

	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragShader);
}