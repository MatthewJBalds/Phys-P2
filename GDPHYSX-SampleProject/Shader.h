#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>


class Shader
{
public:
	GLuint shaderProg;

	Shader(std::string Vert_Path, std::string Frag_Path);

	void Activate();

	void Delete();

public:
	GLuint getShaderProg() const { return shaderProg; }
};
