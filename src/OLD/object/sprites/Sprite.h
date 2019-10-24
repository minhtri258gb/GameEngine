#ifndef SPRITE_H
#define SPRITE_H

#include "SpriteManager.h"


class Sprite {
public:

	// Static
	static SpriteManager* manager;
	static void init();
	static void cleanUp();

	// Constructor
	Sprite(int idTex, float roundTime);
	~Sprite();

	// General
	void update();
	void render();

private:

	// Variable
	int idTex;
	float roundTime, curTime;
};

#endif
