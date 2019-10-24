
#include <glad/glad.h>

#include <glm/glm.hpp>

#include "../../../../Main.h"
#include "VertexBufferMonoID.h"


VertexBufferMonoID::VertexBufferMonoID()
{
	m_ebo = m_count = 0;
}

VertexBufferMonoID::~VertexBufferMonoID()
{
	glDeleteBuffers(1, &m_ebo);
}

void VertexBufferMonoID::draw()
{
	glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, 0);
}

void VertexBufferMonoID::setIndex(vector<unsigned int> indices)
{
	m_count = indices.size();

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * 4, &indices[0], GL_STATIC_DRAW);
}
