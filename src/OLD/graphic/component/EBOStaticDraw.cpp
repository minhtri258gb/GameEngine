
#include <glad/glad.h>

#include "../../../Main.h"
#include "EBOStaticDraw.h"


void EBOStaticDraw::storeData(vector<unsigned int> indices) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}
