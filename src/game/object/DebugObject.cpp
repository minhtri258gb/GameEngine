
#include <glm/glm.hpp>

#include "../../Main.h"
#include "DebugObject.h"

DebugObject::DebugObject()
{
	flag = UNKNOW;
	shader = new DebugShader();
	m_coordinateSystem = new CoordinateSystem();
}

void DebugObject::init(int flag)
{
	this->flag = flag;

	shader->init();

	if(flag & COORDINATE_SYSTEM)
		m_coordinateSystem->init();
}

DebugObject::~DebugObject()
{
	delete shader;
	delete m_coordinateSystem;
}

void DebugObject::update()
{

}

void DebugObject::render()
{
	shader->use();
	shader->loadViewMat();

	if(flag & COORDINATE_SYSTEM)
	{
		shader->loadModelMat(m_coordinateSystem->getTransform());
		m_coordinateSystem->render();
	}
}
