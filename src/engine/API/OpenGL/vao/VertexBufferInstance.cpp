
#include <glad/glad.h>

#include "../../../../Main.h"
#include "VertexBufferInstance.h"


VertexBufferInstance::VertexBufferInstance()
{
	m_vao = 0;
}

void VertexBufferInstance::init(int numAttribute, int lenInstance, int numInstance)
{
	this->numAttribute = numAttribute;

	glGenVertexArrays(1, &m_vao);

	bind();

	vector<vec2> vertices;
	vertices.push_back(vec2(-0.5f, -0.5f));
	vertices.push_back(vec2(0.5f, -0.5f));
	vertices.push_back(vec2(-0.5f, 0.5f));
	vertices.push_back(vec2(0.5f, 0.5f));

	glGenBuffers(1, &m_vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo1);
	glBufferData(GL_ARRAY_BUFFER, 32, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 8, (void*) 0);
	glVertexAttribDivisor(0, 0);

	glGenBuffers(1, &m_vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
	glBufferData(GL_ARRAY_BUFFER, numInstance * lenInstance * 4, NULL, GL_STREAM_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, false, lenInstance * 4, (void*) (0 * 4));
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, lenInstance * 4, (void*) (4 * 4));
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, lenInstance * 4, (void*) (8 * 4));
	glVertexAttribDivisor(3, 1);
	glVertexAttribPointer(4, 4, GL_FLOAT, false, lenInstance * 4, (void*) (12 * 4));
	glVertexAttribDivisor(4, 1);
	glVertexAttribPointer(5, 4, GL_FLOAT, false, lenInstance * 4, (void*) (16 * 4));
	glVertexAttribDivisor(5, 1);
	glVertexAttribPointer(6, 1, GL_FLOAT, false, lenInstance * 4, (void*) (20 * 4));
	glVertexAttribDivisor(6, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unbind();
}

VertexBufferInstance::~VertexBufferInstance()
{
	glDeleteBuffers(1, &m_vbo1);
	glDeleteBuffers(1, &m_vbo2);
	glDeleteVertexArrays(1, &m_vao);
}

void VertexBufferInstance::bind()
{
	glBindVertexArray(m_vao);
	for(int i = 0; i < numAttribute; i++)
		glEnableVertexAttribArray(i);
}

void VertexBufferInstance::unbind()
{
	for(int i = 0; i < numAttribute; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

void VertexBufferInstance::updateBuffer(float *data, int bufferSize)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
	glBufferData(GL_ARRAY_BUFFER, bufferSize * 4, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize * 4, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferInstance::draw(int count)
{
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, count);
}
