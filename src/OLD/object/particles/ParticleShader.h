#ifndef PARTICLESHADER_H
#define PARTICLESHADER_H

#include "../../../engine/API/OpenGL/Shader.h"


class ParticleShader : public Shader {
public:

	// Constructor
	ParticleShader();
	virtual ~ParticleShader();

	// General
	void init();

	// Change data
	void loadNumOfRow(int numOfRow);

private:

	// Variable
	unsigned int numOfRowLoc;
};

#endif
