
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/kernel/System.h"
extern System *g_pSystem;

#include "RigidBody.h"


RigidBody::RigidBody()
{
	core = NULL;
}

RigidBody::~RigidBody()
{
	if(core)
	{
		delete core->getCollisionShape();
		delete core->getMotionState();
		delete core;
	}
}

void RigidBody::getTransForm(vec3 *origin, quat *angle)
{
	btTransform t;
	core->getMotionState()->getWorldTransform(t);

	btVector3 pos = t.getOrigin();
	origin->x = pos.getX();
	origin->y = pos.getY();
	origin->z = pos.getZ();

	btQuaternion rot = t.getRotation();
	*angle = quat(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
}

vec3 RigidBody::getOrigin()
{
	btTransform t;
	core->getMotionState()->getWorldTransform(t);
	btVector3 pos = t.getOrigin();
	return vec3(pos.getX(), pos.getY(), pos.getZ());
}

void RigidBody::loadPlane(vec4 ptPlane, vec3 origin, quat angle, float mass, bool isStatic)
{
	btCollisionShape *plane = new btStaticPlaneShape(
			btVector3(ptPlane.x, ptPlane.y, ptPlane.z), ptPlane.w);
	load(plane, origin, angle, mass, isStatic);
}

void RigidBody::loadBox(vec3 size, vec3 origin, quat angle, float mass, bool isStatic)
{
	btCollisionShape *box = new btBoxShape(btVector3(size.x, size.y, size.z));
	load(box, origin, angle, mass, isStatic);
}

void RigidBody::loadSphere(float rad, vec3 origin, quat angle, float mass, bool isStatic)
{
	btCollisionShape *sphere = new btSphereShape(rad);
	load(sphere, origin, angle, mass, isStatic);
}

bool RigidBody::is(const btCollisionObject *other) const
{
	return (core == other);
}

void RigidBody::setVelocity(vec3 velocity)
{
	core->setLinearVelocity(btVector3(velocity.z, velocity.y, velocity.z));
}

void RigidBody::setUserPointer(void *user)
{
	core->setUserPointer(user);
}

void RigidBody::load(btCollisionShape *shape, vec3 origin, quat angle, float mass, bool isStatic)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(origin.x, origin.y, origin.z));
	t.setRotation(btQuaternion(angle.x, angle.y, angle.z, angle.w));

	btDefaultMotionState *motion = new btDefaultMotionState(t);

	btVector3 inertia(0, 0, 0);
	if (mass != 0)
		shape->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, inertia);
	core = new btRigidBody(info);

	if (isStatic)
		core->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

//	body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
//	body->setCollisionFlags(btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

	g_pSystem->world.add(core);
}
