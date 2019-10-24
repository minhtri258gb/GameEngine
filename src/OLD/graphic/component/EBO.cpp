
#include <glad/glad.h>

#include "EBO.h"



EBO::EBO() {
	glGenBuffers(1, &ID);
}

EBO::~EBO() {
	glDeleteBuffers(1, &ID);
}

void EBO::bindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
