#ifndef __SPRITETEXTURE_H__
#define __SPRITETEXTURE_H__

#include "../graphic/component/Texture.h"


class SpriteTexture {
public:

	// Constructor
	SpriteTexture();
	~SpriteTexture();

	// General
	void bind(int idTex);
	int getNumRow(int idTex);

	// Change data
	int precache(string name);

private:

	// Variable
	vector<Texture*> listTexture;
	vector<int> listNumRow;
};

#endif
