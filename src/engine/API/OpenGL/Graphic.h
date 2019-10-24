#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <GLFW/glfw3.h>


class Graphic
{
public:

	// Constructor / Destructor
	Graphic();
	void init();
	~Graphic();

	// Framework
	void update();
	void render();
	void sync();

	// Get / Set
	int getWindowWidth();
	void setWindowWidth(int);
	int getWindowHeight();
	void setWindowHeight(int);
	mat4 getProjectionMat();
	mat4 getOrthoMat();
	mat4 getViewMat();
	void setViewMat(mat4);
	double getTime();

	// Change data
	void setBlend(bool toogle = false, int type = 0);
	void setCullface(bool toogle = true);
	void setDepth(bool toogle = true);

	// Shader
	unsigned int loadShader(string vertexPath, string fragmentPath);
	void use(unsigned int idProgram);
	unsigned int getLocation(unsigned int idProgram, string nameVariable);
	void setUniform(unsigned int location, int);
	void setUniform(unsigned int location, float);
	void setUniform(unsigned int location, vec2);
	void setUniform(unsigned int location, vec3);
	void setUniform(unsigned int location, vec4);
	void setUniform(unsigned int location, mat4);
	void deleteShader(unsigned int idProgram);

private:

	// Variable
	GLFWwindow *window;
	int m_width, m_height;
	mat4 m_projectionMat, m_orthoMat, m_viewMat;
};

#endif
