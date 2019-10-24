
#include <glad/glad.h>

#include "VAO.h"


VAO::VAO() {
	attributes = 0;
	indexCount = 0;
	ID = 0;
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &ID);
}

void VAO::init(int attributes) {
	glGenVertexArrays(1, &ID);
	this->attributes = attributes;
}

void VAO::bindVAO() {
	glBindVertexArray(ID);
	for(int i=0; i<attributes; i++)
		glEnableVertexAttribArray(i);
}

void VAO::unbind() {
	for(int i=0; i<attributes; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

void VAO::draw(bool ebo) {
	if(ebo)
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, indexCount);

}
