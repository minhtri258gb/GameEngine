#ifndef GROUND_H
#define GROUND_H

#include "GroundShader.h"
#include "../../../engine/API/OpenGL/vao/VertexBufferMonoID.h"
#include "../../../engine/API/OpenGL//texture/Texture2D.h"

class Ground {
public:

	// constructor
	Ground();
	~Ground();

	// general
	void init();
	void render();

private:
	GroundShader* shader;
	VertexBufferMonoID m_vb;
	Texture2D m_texture;
};

#endif
