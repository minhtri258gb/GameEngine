#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "../../file/CFGFile.h"
#include "Sun.h"
#include "../../API/OpenGL/vao/VertexBufferMonoID.h"
#include "../../API/OpenGL/texture/TextureCube.h"


class SkyBox
{
public:

	// Constructor
	SkyBox();
	~SkyBox();

	// General
	void init(string name);
	void render();

	// Get / Set
	vec3 getSunDirect();
	vec3 getSunOrigin();
	vec3 getFogColour();

private:

	// Variable
	unsigned int m_idProgram, m_viewLoc;
	Sun *sun;
	VertexBufferMonoID m_vb;
	TextureCube m_texture;
	vec3 fogColour;
};

#endif
