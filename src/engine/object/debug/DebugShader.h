#ifndef DEBUGSHADER_H_
#define DEBUGSHADER_H_

#include "../../API/OpenGL/Shader.h"


class DebugShader : public Shader
{
public:

	// Constructor
	DebugShader();
	void init();
	virtual ~DebugShader();

	// Change data
	void loadViewMat();
	void loadModelMat(mat4);

private:

	// Variable
	unsigned int viewLoc;
	unsigned int modelLoc;
};

#endif
