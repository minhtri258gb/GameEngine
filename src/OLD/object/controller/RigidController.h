#ifndef __RIGIDCONTROLLER_H__
#define __RIGIDCONTROLLER_H__

#include "Controller.h"
#include "../../physic/component/RigidBody.h"


class RigidController : public Controller
{
public:

	// Constructor
	RigidController(vec3 boundingbox, vec3 origin, quat angle, bool isStatic=false);
	~RigidController();

	// Framework
	void update(vec3* origin, quat* angle);

	// Event
	void force(vec3);

private:

	// Variable
	RigidBody* rigidBody;
};

#endif
