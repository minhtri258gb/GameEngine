#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "../../API/OpenGL/Shader.h"

class TerrainShader: public Shader
{
public:

	// Construcor
	TerrainShader();
	void init();
	virtual ~TerrainShader();

	// Change data
	void loadViewMat();
	void loadLevelQuad(unsigned char levelquad);

private:

	// Variable
	unsigned int viewLoc;
	unsigned int levelQuadLoc;
};

#endif
