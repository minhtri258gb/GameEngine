
#include <glad/glad.h>

#include <glm/glm.hpp>

#include "../../../../Main.h"
#include "VertexBufferNoID.h"

VertexBufferNoID::VertexBufferNoID()
{
	m_count = 0;
}

VertexBufferNoID::~VertexBufferNoID()
{
}

void VertexBufferNoID::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, m_count);
}

void VertexBufferNoID::setCountVertex(unsigned int value)
{
	m_count = value;
}
