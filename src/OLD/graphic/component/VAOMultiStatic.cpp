
#include <glad/glad.h>

#include "../../../Main.h"
#include "VAOMultiStatic.h"


VAOMultiStatic::VAOMultiStatic()
{
	m_ID = 0;
	m_atributes = 0;
}

VAOMultiStatic::~VAOMultiStatic()
{
	for (VBOStaticDraw *vbo : m_vbos)
		delete vbo;

	glDeleteVertexArrays(1, &m_ID);
}

void VAOMultiStatic::init()
{
	glGenVertexArrays(1, &m_ID);
}

void VAOMultiStatic::draw(int meshID)
{
	vector<unsigned int> ebo = m_ebos.at(meshID);
	glDrawElements(GL_TRIANGLES, ebo.size(), GL_UNSIGNED_INT, &ebo[0]);
}

void VAOMultiStatic::bind()
{
	glBindVertexArray(m_ID);
	for (unsigned int i = 0; i < m_atributes; i++)
		glEnableVertexAttribArray(i);
}

void VAOMultiStatic::unbind()
{
	for (unsigned int i = 0; i < m_atributes; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

unsigned int VAOMultiStatic::getNumIndiences() {
	return m_ebos.size();
}

void VAOMultiStatic::addAttribute(vector<vec3> data)
{
	VBOStaticDraw *vbo = new VBOStaticDraw();
	vbo->bindVBO();
	vbo->storeData(data);
	glVertexAttribPointer(m_atributes, 3, GL_FLOAT, GL_FALSE, 12, (void*) 0);
	vbo->unbind();

	m_vbos.push_back(vbo);
	m_atributes++;
}

void VAOMultiStatic::addAttribute(vector<vec2> data)
{
	VBOStaticDraw *vbo = new VBOStaticDraw();
	vbo->bindVBO();
	vbo->storeData(data);
	glVertexAttribPointer(m_atributes, 2, GL_FLOAT, GL_FALSE, 8, (void*) 0);
	vbo->unbind();

	m_vbos.push_back(vbo);
	m_atributes++;
}

void VAOMultiStatic::addIndexBuffer(vector<unsigned int> indices)
{
	m_ebos.push_back(indices);
}
