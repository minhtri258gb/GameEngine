#ifndef __INTERACTIVEENTITY_H__
#define __INTERACTIVEENTITY_H__

#include "../../../OLD/object/Entity.h"
#include "../../../OLD/object/models/Model.h"
#include "../../../OLD/object/controller/RigidController.h"


class InteractiveEntity : public Entity
{
public:

	// Constructor
	InteractiveEntity(string modelname, string modelext, vec3 origin, int angle, float scale);
	~InteractiveEntity();

	// Framework
	void update();
	void render();

private:

	// Variable
	Model* m_model;
	RigidController* m_controller;

	// Change data
	void load(string modelname, string modelext);
};

#endif
