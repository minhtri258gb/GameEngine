#ifndef __EQUIPMENTENTITY_H__
#define __EQUIPMENTENTITY_H__

#include "../../../OLD/object/Entity.h"
#include "../../../engine/object/models/AnimModel.h"


class EquipmentEntity : public Entity
{
public:

	// Constructor
	EquipmentEntity(AnimModel *model, vec3 origin, int angle, float scale);
	~EquipmentEntity();

	// Framework
	void update();
	void render();

	// Event
	void primaryAction();
	void secondAction();

private:

	// Variable
	AnimModel* m_model;
};

#endif
