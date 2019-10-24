
#include <glad/glad.h>

#include "VBO.h"


VBO::VBO() {
	glGenBuffers(1, &ID);
}

VBO::~VBO() {
	glDeleteBuffers(1, &ID);
}

void VBO::bindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
