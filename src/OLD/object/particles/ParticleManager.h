#ifndef __PARTICLEMANAGER_H__
#define __PARTICLEMANAGER_H__

#include "ParticleShader.h"
#include "../SpriteTexture.h"
#include "../../graphic/component/VAOStaticDraw.h"


class ParticleManager
{
public:

	// Variable
	ParticleShader* shader;
	SpriteTexture* texture;
	unsigned int vaoID, vboID1, vboID2;

	const short MAX_INSTANCE = 1024;
	const short INSTANCE_DATA_LENGTH = 21;

	// Constructor / Destructor
	ParticleManager();
	void init();
	~ParticleManager();
};

#endif
