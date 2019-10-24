#ifndef MODELSHADER_H
#define MODELSHADER_H

#include "../../../engine/API/OpenGL/Shader.h"


class ModelShader : public Shader
{
public:

	// Constructor
	ModelShader();
	virtual ~ModelShader();

	// General
	void init();

	// Change data
	void loadViewMat();
	void loadModelMat(mat4);

private:

	// Variable
	unsigned int modelLoc;
	unsigned int viewLoc;
};

#endif
