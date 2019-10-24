#ifndef FONTSHADER_H
#define FONTSHADER_H

#include "../../../engine/API/OpenGL/Shader.h"


class FontShader: public Shader {
public:

	// Constructor
	FontShader();
	virtual ~FontShader();

	// General
	void init();

	void loadColor(float r, float g, float b);

private:
	unsigned int colorLoc;
};

#endif

