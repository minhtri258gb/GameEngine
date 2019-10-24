
#include <glm/gtx/transform.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "QuadTreeVision.h"


QuadTreeVision::QuadTreeVision()
{
}

void QuadTreeVision::init(float minX, float maxX, float minZ, float maxZ)
{
	vector<vec3> vertices;
	vertices.push_back(vec3(minX, 0.0f, minZ));
	vertices.push_back(vec3(maxX, 0.0f, minZ));
	vertices.push_back(vec3(minX, 0.0f, maxZ));
	vertices.push_back(vec3(maxX, 0.0f, maxZ));

	vector<vec3> colour;
	colour.push_back(vec3(0.0f, 0.0f, 0.0f));
	colour.push_back(vec3(1.0f, 0.0f, 0.0f));
	colour.push_back(vec3(1.0f, 1.0f, 1.0f));
	colour.push_back(vec3(0.0f, 1.0f, 0.0f));

	vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	m_vb.init();
	m_vb.bind();
	m_vb.addAttribute(vertices);
	m_vb.addAttribute(colour);
	m_vb.setIndex(indices);
	m_vb.unbind();
}

QuadTreeVision::~QuadTreeVision()
{
}

void QuadTreeVision::update()
{
}

void QuadTreeVision::render()
{
	engine.m_debugObject->shader->use();
	engine.m_debugObject->shader->loadViewMat();

	mat4 tran = translate(mat4(), vec3(0,200,0));

	engine.m_debugObject->shader->loadModelMat(tran);

	glDisable(GL_CULL_FACE);

	m_vb.bind();
	m_vb.draw();
	m_vb.unbind();

	glEnable(GL_CULL_FACE);
}
