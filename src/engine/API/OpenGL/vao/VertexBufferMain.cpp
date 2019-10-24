
#include <glad/glad.h>

#include "../../../../Main.h"
#include "VertexBufferMain.h"


VertexBufferMain::VertexBufferMain()
{
	m_vao = 0;
	m_ebo = 0;
}

void VertexBufferMain::init()
{
	glGenVertexArrays(1, &m_vao);
}

VertexBufferMain::~VertexBufferMain()
{
	glDeleteBuffers(1, &m_ebo);

	for(unsigned int vbo : m_vbos)
		glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &m_vao);
}

void VertexBufferMain::bind()
{
	glBindVertexArray(m_vao);
	for(unsigned int i = 0; i < m_vbos.size(); i++)
		glEnableVertexAttribArray(i);
}

void VertexBufferMain::unbind()
{
	for(unsigned int i = 0; i < m_vbos.size(); i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

void VertexBufferMain::drawArrays(int start, int count)
{
	glDrawArrays(GL_TRIANGLES, start, count);
}

void VertexBufferMain::drawElements(int count, unsigned int *indices)
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, indices);
}

void VertexBufferMain::addAttribute(vector<vec3> data)
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

void VertexBufferMain::addAttribute(vector<ivec3> data)
{
	int attribute = m_vbos.size();
	glEnableVertexAttribArray(attribute);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * 12, &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attribute, 3, GL_INT, GL_FALSE, 12, (void*) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vbos.push_back(vbo);
}

void VertexBufferMain::addAttribute(vector<vec2> data)
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

void VertexBufferMain::setIndex(vector<unsigned int> indices)
{
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, &indices[0], GL_STATIC_DRAW);
}
