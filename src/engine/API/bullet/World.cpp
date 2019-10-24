
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../kernel/Timer.h"
extern Timer *g_pTimer;

#include "World.h"


bool callbackFunc(btManifoldPoint &cp, const btCollisionObjectWrapper *obj1, int partID1, int index1, const btCollisionObjectWrapper *obj2, int partID2,
		int index2);


World::World()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
}

World::~World()
{
	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}

void World::init()
{
//	addPlane(Vec4(0,1,0,0), Vec3(), 0.0f);

	dynamicsWorld->setGravity(btVector3(0, -627.84f, 0));

	gContactAddedCallback = callbackFunc;
}

void World::update()
{
	dynamicsWorld->stepSimulation(g_pTimer->getTimePassed());
}

void World::add(btRigidBody *body)
{
	dynamicsWorld->addRigidBody(body);
}

void World::add(btPairCachingGhostObject *body, btKinematicCharacterController *controller)
{
	dynamicsWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	dynamicsWorld->addCollisionObject(body, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
	dynamicsWorld->addAction(controller);
}

void World::addTerrain(int width, int depth, float *data, float scale)
{

	int hlength = width * depth;
	float hmin, hmax;
	hmax = hmin = *data;
	for(int i = 1; i < hlength; i++)
	{
		float h = *(data + i);
		if(h > hmax)
			hmax = h;
		else if(h < hmin)
			hmin = h;
	}

	btHeightfieldTerrainShape *terrain = new btHeightfieldTerrainShape(width, depth, &data[0], 1.0f, hmin, hmax, 1, PHY_FLOAT, false);

	terrain->setUseDiamondSubdivision(true);
	terrain->setLocalScaling(btVector3(scale, 1.0f, scale));
	terrain->setMargin(128.0f);

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3((width - 1) * scale / 2, (hmin + hmax) / 2.0f, (depth - 1) * scale / 2));
	btDefaultMotionState *motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0f, motion, terrain, btVector3(0, 0, 0));

	btRigidBody *body = new btRigidBody(info);
	body->setFriction(0.8);
	body->setHitFraction(0.8);
	body->setRestitution(0.6);
	body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	body->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(body);
}

bool World::raycast(const vec3 &start, vec3 &end, vec3 &normal)
{

	btVector3 btStart = btVector3(start.x, start.y, start.z);
	btVector3 btEnd = btVector3(end.x, end.y, end.z);
	btVector3 btNormal;

	btCollisionWorld::ClosestRayResultCallback rayCallback(btStart, btEnd);
//	rayCallback.m_collisionFilterMask = FILTER_CAMERA;

// Perform raycast
	dynamicsWorld->rayTest(btStart, btEnd, rayCallback);

	if(rayCallback.hasHit())
	{
		btEnd = rayCallback.m_hitPointWorld;
		btNormal = rayCallback.m_hitNormalWorld;
		end = vec3(btEnd.getX(), btEnd.getY(), btEnd.getZ());
		normal = vec3(btNormal.getX(), btNormal.getY(), btNormal.getZ());
		return true;
	}

	return false;
}

bool World::raycast(const vec3 &start, vec3 &end, void *&pUser)
{

	btVector3 btStart = btVector3(start.x, start.y, start.z);
	btVector3 btEnd = btVector3(end.x, end.y, end.z);

	btCollisionWorld::ClosestRayResultCallback rayCallback(btStart, btEnd);
//	rayCallback.m_collisionFilterMask = FILTER_CAMERA;

// Perform raycast
	dynamicsWorld->rayTest(btStart, btEnd, rayCallback);

	if(rayCallback.hasHit())
	{
		btEnd = rayCallback.m_hitPointWorld;
		end = vec3(btEnd.getX(), btEnd.getY(), btEnd.getZ());
		pUser = rayCallback.m_collisionObject->getUserPointer();
		return true;
	}

	return false;
}

bool callbackFunc(btManifoldPoint &cp, const btCollisionObjectWrapper *obj1, int partID1, int index1, const btCollisionObjectWrapper *obj2, int partID2,
		int index2)
{

	cout << "collision" << endl;
	return false;
}
