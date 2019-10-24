#ifndef __WORLD_H__
#define __WORLD_H__

//#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include "../../../Old/physic/component/RigidBody.h"
#include "../../../Old/physic/component/ControlBody.h"


class World
{
public:

	// Constructor
	World();
	~World();

	// General
	void init();
	void update();

	// Change data
	void add(btRigidBody*);
	void add(btPairCachingGhostObject* body, btKinematicCharacterController* controller);
	void addTerrain(int width, int depth, float* data, float scale);

	// Check
	bool raycast(const vec3 &start, vec3 &end, vec3 &normal);
	bool raycast(const vec3 &start, vec3 &end, void* &pUser);

private:

	// Variable
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
};

#endif
