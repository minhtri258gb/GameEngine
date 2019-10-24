#ifndef __COMMONENTITY_H__
#define __COMMONENTITY_H__

#include "../../../OLD/object/Entity.h"
#include "../../../engine/object/models/StaticModel.h"
// #include "../../../OLD/object/controller/RigidController.h"


class CommonEntity : public Entity
{
public:

	// Constructor
	CommonEntity(StaticModel *model, vec3 origin, int angle, float scale);
	~CommonEntity();

	// Framework
	void update();
	void render();

private:

	// Variable
	StaticModel* m_model;
	// RigidController* m_controller;
};

#endif
