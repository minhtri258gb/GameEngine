#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "TerrainShader.h"
#include "../../API/OpenGL/vao/VertexBufferDynamic.h"
#include "../../API/OpenGL/texture/Texture2DPack.h"


class Terrain
{
public:

	// Variable
	VertexBufferDynamic m_vb;
	float m_maxwidth, m_maxlength;

	// Constructor
	Terrain();
	void init(string name);
	~Terrain();

	// Framework
	void renderPre();
	void render(vec2 origin, unsigned short level, mt::flag patch);
	void renderPost();

	// Get / Set
	unsigned short getHeightGrid(int x, int z);
	float getHeightAny(unsigned short x, unsigned short z);

private:

	// Variable
	TerrainShader* shader;
	Texture2DPack m_texture;
	vector<float> heightmap, heightmapPhysic;

};

#endif
