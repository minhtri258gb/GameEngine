#ifndef __BODYBOX_H__
#define __BODYBOX_H__

#include "../../../OLD/physic/component/RigidBody.h"


class BodyBox
{
public:

	// Constructor / Destructor
	BodyBox(vec3 boundingbox, vec3 origin, quat angle, bool isStatic=false);
	~BodyBox();

	// Framework
	void update(vec3* origin, quat* angle);

	// Event
	void force(vec3);

	// Get / Set
	void setUser(void *user);

private:

	// Variable
	RigidBody* rigidBody;

};

#endif
