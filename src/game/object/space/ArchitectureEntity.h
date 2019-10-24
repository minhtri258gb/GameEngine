#ifndef __ARCHITECTUREENTITY_H__
#define __ARCHITECTUREENTITY_H__

#include "../../../OLD/object/Entity.h"
#include "../../../OLD/object/models/Model.h"
#include "../../../OLD/object/controller/RigidController.h"


class ArchitectureEntity : public Entity
{
public:

	// Constructor
	ArchitectureEntity(string modelname, string modelext, vec3 origin, int angle, float scale);
	~ArchitectureEntity();

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
