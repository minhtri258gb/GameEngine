
#include <sstream>
#include <glad/glad.h>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../kernel/System.h"
extern System *g_pSystem;

#include "Shader.h"


Shader::Shader()
{
	this->ID = 0;
}

Shader::~Shader()
{
	//dtor
}

void Shader::load(string vertexPath, string fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	// open files
	ifstream vShaderFile(vertexPath.c_str());
	ifstream fShaderFile(fragmentPath.c_str());

	if(vShaderFile.fail() || fShaderFile.fail())
	{
		g_pSystem->error("[Shader] File not successfully read: " + vertexPath + " or " + fragmentPath);
		return;
	}

	// read file's buffer contents into streams
	stringstream vShaderStream, fShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	// close file handlers
	vShaderFile.close();
	fShaderFile.close();

	string vertexCode = vShaderStream.str();
	string fragmentCode = fShaderStream.str();

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

unsigned int Shader::getLocation(string name)
{
	return glGetUniformLocation(ID, name.c_str());
}

void Shader::setInt(unsigned int location, int value)
{
	glUniform1i(location, value);
}

void Shader::setFloat(unsigned int location, float value)
{
	glUniform1f(location, value);
}

void Shader::setVec2(unsigned int location, vec2 value)
{
	glUniform2f(location, value.x, value.y);
}

void Shader::setVec3(unsigned int location, vec3 value)
{
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setVec4(unsigned int location, vec4 value)
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setMat4(unsigned int location, mat4 value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shader::checkCompileErrors(unsigned int shader, string type)
{
	int success;
	char infoLog[1024];
	if(!(type == "PROGRAM"))
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			cout << "[Shader] Compilation error of type: " + type + "\n" + infoLog + "\n -- ------------------------------- -- " << endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			cout << "[Shader] Linking error of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
		}
	}
}
