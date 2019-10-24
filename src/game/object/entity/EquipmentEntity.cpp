
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/kernel/View.h"
extern View *g_pView;

#include "EquipmentEntity.h"


EquipmentEntity::EquipmentEntity(AnimModel *model, vec3 origin, int angle, float scale)
{
	m_origin = origin;
	m_angle = angleAxis(radians((float)angle), vec3(0,1,0));
	m_scale = scale;
	m_model = model;
}

EquipmentEntity::~EquipmentEntity()
{
}

void EquipmentEntity::update()
{
	// m_controller->update(&m_origin, &m_angle);
	m_model->update();
}

void EquipmentEntity::render()
{
	// g_pView->getQuat() * m_angle
	m_model->render(m_origin, quat(), m_scale);
	// m_model->render(g_pView->getPosition() + m_origin, quat(), m_scale);
}

void EquipmentEntity::primaryAction()
{
	cout << "run" << endl;
}

void EquipmentEntity::secondAction()
{

}
