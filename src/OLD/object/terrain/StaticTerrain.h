#ifndef STATICTERRAIN_H
#define STATICTERRAIN_H

#include "../../../engine/file/CFGFile.h"
#include "../../../engine/object/terrain/TerrainShader.h"
#include "../../../OLD/graphic/component/VAOStaticDraw.h"
#include "../../../OLD/graphic/component/Texture.h"



class StaticTerrain {
public:

	// constructor
	StaticTerrain();
	virtual ~StaticTerrain();

	// general
	void init(CFGFile*);
	void render();

private:
	TerrainShader* shader;
	VAOStaticDraw* vao;
	Texture* texture;
};

#endif
