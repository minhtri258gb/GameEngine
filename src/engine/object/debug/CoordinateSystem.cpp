
#include <glm/gtx/transform.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../kernel/View.h"
extern View *g_pView;

#include "CoordinateSystem.h"


CoordinateSystem::CoordinateSystem()
{
}

void CoordinateSystem::init()
{
	vector<vec3> vertices;
	vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
	vertices.push_back(vec3(99.0f, 1.0f, 1.0f));
	vertices.push_back(vec3(99.0f, -1.0f, -1.0f));
	vertices.push_back(vec3(1.0f, 99.0f, 1.0f));
	vertices.push_back(vec3(-1.0f, 99.0f, -1.0f));
	vertices.push_back(vec3(1.0f, 1.0f, 99.0f));
	vertices.push_back(vec3(-1.0f, -1.0f, 99.0f));

	vector<vec3> colour;
	colour.push_back(vec3(0.0f, 0.0f, 0.0f));
	colour.push_back(vec3(1.0f, 0.0f, 0.0f));
	colour.push_back(vec3(1.0f, 0.0f, 0.0f));
	colour.push_back(vec3(0.0f, 1.0f, 0.0f));
	colour.push_back(vec3(0.0f, 1.0f, 0.0f));
	colour.push_back(vec3(0.0f, 0.0f, 1.0f));
	colour.push_back(vec3(0.0f, 0.0f, 1.0f));

	vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(6);

	m_vb.init();
	m_vb.bind();
	m_vb.addAttribute(vertices);
	m_vb.addAttribute(colour);
	m_vb.setIndex(indices);
	m_vb.unbind();
}

CoordinateSystem::~CoordinateSystem()
{
}

void CoordinateSystem::render()
{
	glDisable(GL_CULL_FACE);

	m_vb.bind();
	m_vb.draw();
	m_vb.unbind();

	glEnable(GL_CULL_FACE);
}

mat4 CoordinateSystem::getTransform()
{
	vec3 ov = g_pView->getPosition() + g_pView->getVeclook();
	mat4 tranform = translate(mat4(), ov * 100.0f);
	return tranform;
}
