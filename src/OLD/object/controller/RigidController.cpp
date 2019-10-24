
#include "../../../Main.h"
#include "RigidController.h"


RigidController::RigidController(vec3 boundingbox, vec3 origin, quat angle, bool isStatic)
{
	rigidBody = new RigidBody();
	rigidBody->loadBox(boundingbox, origin, angle, 1.0f, isStatic);
}

RigidController::~RigidController()
{
	delete rigidBody;
}

void RigidController::update(vec3* origin, quat* angle)
{
	rigidBody->getTransForm(origin, angle);
}

void RigidController::force(vec3 velocity)
{
	rigidBody->setVelocity(velocity);
}
