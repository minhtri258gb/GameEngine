#ifndef SPRITESHADER_H
#define SPRITESHADER_H

#include "../../../engine/API/OpenGL/Shader.h"


class SpriteShader: public Shader
{
public:

	// Constructor / Destructor
	SpriteShader();
	virtual ~SpriteShader();

	// General
	void init();

	// Change data
	void loadMatViewModel(mat4);
	void loadOffsetTex(vec4);
	void loadBlendFactor(float);
	void loadNumOfRow(int);

private:

	// Variable
	unsigned int matViewModelLoc;
	unsigned int offsetTexLoc;
	unsigned int blendFactorLoc;
	unsigned int numOfRowLoc;
};

#endif
