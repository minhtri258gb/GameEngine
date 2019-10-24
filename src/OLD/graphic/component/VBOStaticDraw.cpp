#include <glad/glad.h>

#include "../../../Main.h"
#include "VBOStaticDraw.h"

void VBOStaticDraw::storeData(vector<vec3> data)
{
	glBufferData(GL_ARRAY_BUFFER, data.size() * 12, &data[0], GL_STATIC_DRAW);
}

void VBOStaticDraw::storeData(vector<vec2> data)
{
	glBufferData(GL_ARRAY_BUFFER, data.size() * 8, &data[0], GL_STATIC_DRAW);
}
