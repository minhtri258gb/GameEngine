#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include <bullet/btBulletDynamicsCommon.h>


class RigidBody
{
public:

	// Constructor
	RigidBody();
	~RigidBody();

	// Get / Set
	void getTransForm(vec3* origin, quat* angle);
	vec3 getOrigin();

	// Change data
	void loadPlane(vec4 ptPlane, vec3 origin, quat angle, float mass, bool isStatic);
	void loadBox(vec3 size, vec3 origin, quat angle, float mass, bool isStatic);
	void loadSphere(float rad, vec3 origin, quat angle, float mass, bool isStatic);

	// Check
	bool is(const btCollisionObject* other) const;

	// Event
	void setVelocity(vec3 velocity);

	// Get / Set
	void setUserPointer(void *user);

private:

	// Variable
	btRigidBody* core;

	// Change data
	void load(btCollisionShape*, vec3 origin, quat angle, float mass, bool isStatic);
};

#endif
