#include "Shader.h"

Shader::Shader(std::string Vert_Path, std::string Frag_Path)
{
	std::ifstream vert_file(Vert_Path);
	std::stringstream vert_buffer;
	vert_buffer << vert_file.rdbuf();
	std::string vert_string = vert_buffer.str();
	const char* vert_source = vert_string.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert_source, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex Shader Compilation Failed: " << infoLog << std::endl;
	}

	std::ifstream frag_file(Frag_Path);
	std::stringstream frag_buffer;
	frag_buffer << frag_file.rdbuf();
	std::string frag_string = frag_buffer.str();
	const char* frag_source = frag_string.c_str();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag_source, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment Shader Compilation Failed: " << infoLog << std::endl;
	}

	this->shaderProg = glCreateProgram();
	glAttachShader(this->shaderProg, vertexShader);
	glAttachShader(this->shaderProg, fragmentShader);
	glLinkProgram(this->shaderProg);

	glGetProgramiv(this->shaderProg, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProg, 512, NULL, infoLog);
		std::cout << "Shader Linking Failed: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(this->shaderProg);
}

void Shader::Delete()
{
	glDeleteProgram(this->shaderProg);
}
