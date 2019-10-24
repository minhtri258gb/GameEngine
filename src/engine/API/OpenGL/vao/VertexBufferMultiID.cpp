
#include <glad/glad.h>

#include <glm/glm.hpp>

#include "../../../../Main.h"
#include "VertexBufferMultiID.h"

VertexBufferMultiID::VertexBufferMultiID()
{
}

VertexBufferMultiID::~VertexBufferMultiID()
{
}

void VertexBufferMultiID::draw(unsigned int index)
{
	unsigned int offset = m_part[index];
	unsigned int count = offset - index ? (m_part[index-1]) : 0;

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, &m_ebo[offset]);
}

unsigned int VertexBufferMultiID::getNumPart()
{
	return m_part.size();
}

void VertexBufferMultiID::setIndex(vector<unsigned int> indices)
{
	m_ebo = indices;
}

void VertexBufferMultiID::setPart(vector<unsigned int> part)
{
	m_part = part;
}
