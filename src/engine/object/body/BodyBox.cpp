
#include "../../../Main.h"
#include "BodyBox.h"


BodyBox::BodyBox(vec3 boundingbox, vec3 origin, quat angle, bool isStatic)
{
	rigidBody = new RigidBody();
	rigidBody->loadBox(boundingbox, origin, angle, 1.0f, isStatic);
}

BodyBox::~BodyBox()
{
	delete rigidBody;
}

void BodyBox::update(vec3* origin, quat* angle)
{
	rigidBody->getTransForm(origin, angle);
}

void BodyBox::force(vec3 velocity)
{
	rigidBody->setVelocity(velocity);
}

void BodyBox::setUser(void *user)
{
	rigidBody->setUserPointer(user);
}
