#ifndef __CHARACTERCONTROLLER_H__
#define __CHARACTERCONTROLLER_H__

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>


class ControlBody
{
public:

	// Constructor
	ControlBody();
	~ControlBody();

	// General

	// Get / Set
	vec3 getOrigin();
	void setGravity(float gravity);

	// Change data
	void loadCapsule(vec3 origin);

	// Check
	bool onGround();

	// Event
	void setWalkDirection(vec3 velocity);
	void setVelocity(vec3 velocity);
	void jump(float force);

private:

	// Variable
	btKinematicCharacterController* controller;
	bool m_onGround;

	// Change data
    void load(btConvexShape* shape, vec3 origin);

};

#endif
