#ifndef GROUNDSHADER_H
#define GROUNDSHADER_H

#include "../../../engine/API/OpenGL/Shader.h"


class GroundShader: public Shader {
public:

	// constructor
	GroundShader();
	virtual ~GroundShader();

	// general
	void init();

	void loadViewMat();

private:
	unsigned int viewLoc;
};

#endif
