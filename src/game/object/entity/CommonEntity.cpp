
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/file/CFGFile.h"

#include "CommonEntity.h"


CommonEntity::CommonEntity(StaticModel *model, vec3 origin, int angle, float scale)
{
	m_origin = origin;
	m_angle = angleAxis(radians((float)angle), vec3(0,1,0));
	m_scale = scale;
	m_model = model;
	// m_controller = NULL;
}

CommonEntity::~CommonEntity()
{
	// delete m_controller;
}

void CommonEntity::update()
{
	// m_controller->update(&m_origin, &m_angle);
}

void CommonEntity::render()
{
	m_model->render(m_origin, m_angle, m_scale);
}
