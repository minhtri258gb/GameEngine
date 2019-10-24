
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/kernel/System.h"
extern System *g_pSystem;

#include "ControlBody.h"


ControlBody::ControlBody()
{
	controller = NULL;
	m_onGround = false;
}

ControlBody::~ControlBody()
{
	//dtor
}

vec3 ControlBody::getOrigin()
{
	btVector3 origin = controller->getGhostObject()->getWorldTransform().getOrigin();
	return vec3(origin.getX(), origin.getY(), origin.getZ());
}

void ControlBody::setGravity(float gravity)
{
	controller->setGravity(btVector3(0, -gravity, 0));
}

void ControlBody::loadCapsule(vec3 origin)
{
	btConvexShape *ghostShape = new btCapsuleShape(10.0f, 48.0f); // 68
	load(ghostShape, origin);
}

void ControlBody::setWalkDirection(vec3 velocity)
{
	controller->setWalkDirection(btVector3(velocity.x, velocity.y, velocity.z));
}

void ControlBody::setVelocity(vec3 velocity)
{
	controller->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}

void ControlBody::jump(float force)
{
	if(controller->canJump())
		controller->jump(btVector3(0, force, 0));
}

bool ControlBody::onGround()
{
	return controller->onGround();
}

void ControlBody::load(btConvexShape *shape, vec3 origin)
{
	btPairCachingGhostObject *ghostObject = new btPairCachingGhostObject();
	ghostObject->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(origin.x, origin.y, origin.z)));
	ghostObject->setCollisionShape(shape);
	ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

	controller = new btKinematicCharacterController(ghostObject, shape, 25.0f, btVector3(0, 1, 0));
	controller->setUseGhostSweepTest(false);
	controller->setUpInterpolate(true);
	controller->setAngularDamping(1.0f); // Khong xoay quan tinh
	controller->setFallSpeed(1024.0f); // ?
	controller->setGravity(btVector3(0, -1024.0f, 0));

	controller->warp(btVector3(origin.x, origin.y, origin.z));

	g_pSystem->world.add(ghostObject, controller);
}
