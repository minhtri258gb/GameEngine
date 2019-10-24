
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../kernel/System.h"
extern System *g_pSystem;

#include "../../kernel/View.h"
extern View *g_pView;

#include "../../kernel/Command.h"
extern Command *g_pCommand;

#include "Graphic.h"


void cbk_mouse(GLFWwindow *window, double xpos, double ypos);
void cbk_key(GLFWwindow *window, int key, int scancode, int action, int mods);
void cbk_mouse_button(GLFWwindow *window, int button, int action, int mods);

double mouseLastX, mouseLastY;


Graphic::Graphic()
{
	window = NULL;

	m_width = 1280;
	m_height = 720;
}

void Graphic::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(m_width, m_height, "Game Engine", NULL, NULL); // window
	// window = glfwCreateWindow(width, height, windowName.toCStr(), glfwGetPrimaryMonitor(), NULL);
	if(window == NULL)
	{
		g_pSystem->error("[Window] Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Set icon
	// GLFWimage icons[2];
	// icons[0].pixels = stbi_load("res/system/logo.ico", &icons[0].width, &icons[0].height, 0, 4);
	// if(icons[0].pixels) {
	// 	icons[1] = icons[0];
	// 	glfwSetWindowIcon(window, 2, icons);
	// }

	glfwSetCursorPosCallback(window, cbk_mouse);
	glfwSetKeyCallback(window, cbk_key);
	glfwSetMouseButtonCallback(window, cbk_mouse_button);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		g_pSystem->error("[Window] Failed to initialize GLAD");
		return;
	}

	// Some else
	glfwSetCursorPos(window, 0, 0);

	// OpenGL StartUp
	glViewport(0, 0, m_width, m_height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// glEnable(GL_MULTISAMPLE);

	// INIT MATRIX
	m_projectionMat = perspective(radians((float) g_pView->getFOV()),
						(float) m_width / (float) m_height,
						(float) g_pView->getNear(), (float) g_pView->getFar());

	m_orthoMat = ortho(0.0f, (float) m_width, 0.0f, (float) m_height);
}

Graphic::~Graphic()
{
	glfwTerminate();
}

void Graphic::update()
{
	if(glfwWindowShouldClose(window))
		g_pSystem->exit();
}

void Graphic::render()
{
	glClear(GL_DEPTH_BUFFER_BIT); // |GL_COLOR_BUFFER_BIT
}

void Graphic::sync()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int Graphic::getWindowWidth()
{
	return m_width;
}

void Graphic::setWindowWidth(int value)
{
	m_width = value;
}

int Graphic::getWindowHeight()
{
	return m_height;
}

void Graphic::setWindowHeight(int value)
{
	m_height = value;
}

mat4 Graphic::getProjectionMat()
{
	return m_projectionMat;
}

mat4 Graphic::getOrthoMat()
{
	return m_orthoMat;
}

mat4 Graphic::getViewMat()
{
	return m_viewMat;
}

void Graphic::setViewMat(mat4 value)
{
	m_viewMat = value;
}

double Graphic::getTime()
{
	return glfwGetTime();
}

void Graphic::setBlend(bool toogle, int type)
{
	if(toogle)
	{
		switch (type)
		{
			case 1: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
			case 2: glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
		}
		glEnable(GL_BLEND);
	}
	else glDisable(GL_BLEND);
}

void Graphic::setCullface(bool toogle)
{
	if(toogle) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
}

void Graphic::setDepth(bool toogle)
{
	if(toogle) glDepthMask(GL_TRUE);
	else glDepthMask(GL_FALSE);
}

unsigned int Graphic::loadShader(string vertexPath, string fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	// open files
	ifstream vShaderFile(vertexPath.c_str());
	ifstream fShaderFile(fragmentPath.c_str());

	if(vShaderFile.fail() || fShaderFile.fail())
	{
		g_pSystem->error("[Shader] File not successfully read: " + vertexPath + " or " + fragmentPath);
		return 0;
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
	int success;
	char infoLog[1024];
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		cout << "[Shader] Compilation error of type: VERTEX\n" + string(infoLog) + "\n -- ------------------------------- -- " << endl;
	}
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		cout << "[Shader] Compilation error of type: FRAGMENT\n" + string(infoLog) + "\n -- ------------------------------- -- " << endl;
	}
	// shader Program
	unsigned int ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infoLog);
		cout << "[Shader] Linking error of type: PROGRAM\n" << string(infoLog) << "\n -- ------------------------------- -- " << endl;
	}
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return ID;
}

void Graphic::use(unsigned int idProgram)
{
	glUseProgram(idProgram);
}

unsigned int Graphic::getLocation(unsigned int idProgram, string nameVariable)
{
	return glGetUniformLocation(idProgram, nameVariable.c_str());
}

void Graphic::setUniform(unsigned int location, int value)
{
	glUniform1i(location, value);
}

void Graphic::setUniform(unsigned int location, float value)
{
	glUniform1f(location, value);
}

void Graphic::setUniform(unsigned int location, vec2 value)
{
	glUniform2f(location, value.x, value.y);
}

void Graphic::setUniform(unsigned int location, vec3 value)
{
	glUniform3f(location, value.x, value.y, value.z);
}

void Graphic::setUniform(unsigned int location, vec4 value)
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Graphic::setUniform(unsigned int location, mat4 value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
}

void Graphic::deleteShader(unsigned int idProgram)
{
	glDeleteShader(idProgram);
}

void cbk_mouse(GLFWwindow *window, double xpos, double ypos)
{
	double xoffset = xpos - mouseLastX;
	double yoffset = mouseLastY - ypos;

	mouseLastX = xpos;
	mouseLastY = ypos;

	g_pView->processMouseMovement(xoffset, yoffset);
}

void cbk_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == -1)
		return;
	if(action == GLFW_PRESS)
		g_pCommand->keyPress(key, true);
	else if(action == GLFW_RELEASE)
		g_pCommand->keyPress(key, false);
}

void cbk_mouse_button(GLFWwindow *window, int button, int action, int mods)
{
	bool press;
	switch (action) {
	case GLFW_PRESS:
		press = true;
		break;
	case GLFW_RELEASE:
		press = false;
		break;
	default:
		return;
	}

	if(button > 2)
		return;

	g_pCommand->keyPress(351 + button, press);
}
