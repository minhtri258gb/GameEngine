
#include <glad/glad.h>

#include "../../../../Main.h"
#include "VertexBufferDynamic.h"


VertexBufferDynamic::VertexBufferDynamic()
{
	m_vao = m_ebo = 0;
	m_nAttr = m_count = 0;
	m_vbos = NULL;
}

void VertexBufferDynamic::init(int attribute)
{
	m_nAttr = attribute;
	m_vbos = new unsigned int[attribute];

	glGenVertexArrays(1, &m_vao);
	for(int i=0; i<attribute; i++)
		glGenBuffers(1, &m_vbos[i]);
	glGenBuffers(1, &m_ebo);
}

void VertexBufferDynamic::storaAttribute(int attribute, int vecNum, int sizeArr)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[attribute]);
	glBufferData(GL_ARRAY_BUFFER, sizeArr * vecNum * 4, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attribute, vecNum, GL_FLOAT, GL_FALSE, vecNum * 4, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferDynamic::storaIndex(short sizeArr)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArr * 4, NULL, GL_DYNAMIC_DRAW);
}

VertexBufferDynamic::~VertexBufferDynamic()
{
	glDeleteBuffers(1, &m_ebo);
	for(unsigned int i=0; i<m_nAttr; i++)
		glDeleteBuffers(1, &m_vbos[i]);
	glDeleteVertexArrays(1, &m_vao);

	delete[] m_vbos;
}

void VertexBufferDynamic::bind()
{
	glBindVertexArray(m_vao);
	for(unsigned int i = 0; i < m_nAttr; i++)
		glEnableVertexAttribArray(i);
}

void VertexBufferDynamic::draw()
{
	glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, 0);
}

void VertexBufferDynamic::unbind()
{
	for(unsigned int i = 0; i < m_nAttr; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

void VertexBufferDynamic::updateAttribute(int attribute, vector<vec2> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[attribute]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * 8, &data[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferDynamic::updateAttribute(int attribute, vector<vec3> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[attribute]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * 12, &data[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferDynamic::updateIndex(vector<unsigned int> indices)
{
	m_count = indices.size();
	glGenBuffers(1, &m_ebo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * 4, &indices[0]);
}
