
#include <glad/glad.h>

#include "../../../../Main.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	m_vao = 0;
}

void VertexBuffer::init()
{
	glGenVertexArrays(1, &m_vao);
}

VertexBuffer::~VertexBuffer()
{
	for(unsigned int vbo : m_vbos)
		glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &m_vao);
}

void VertexBuffer::bind()
{
	glBindVertexArray(m_vao);
	for(unsigned int i = 0; i < m_vbos.size(); i++)
		glEnableVertexAttribArray(i);
}

void VertexBuffer::unbind()
{
	for(unsigned int i = 0; i < m_vbos.size(); i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

void VertexBuffer::addAttribute(vector<vec3> data)
{
	int attribute = m_vbos.size();
	glEnableVertexAttribArray(attribute);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * 12, &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 12, (void*) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vbos.push_back(vbo);
}

void VertexBuffer::addAttribute(vector<vec2> data)
{
	int attribute = m_vbos.size();
	glEnableVertexAttribArray(attribute);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * 8, &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, 8, (void*) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vbos.push_back(vbo);
}
