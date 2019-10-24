#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "SpriteShader.h"
#include "../SpriteTexture.h"
#include "../../graphic/component/VAOStaticDraw.h"


class SpriteManager {
public:

	// Variable
	SpriteShader* shader;
	SpriteTexture* texture;
	VAOStaticDraw* vao;

	// Constructor
	SpriteManager();
	~SpriteManager();

	// General
	void init();

protected:

private:
};

#endif
