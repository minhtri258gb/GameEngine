
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/kernel/Timer.h"
extern Timer *g_pTimer;

#include "Particle.h"


Particle::Particle(float gravity)
{
	life = 0;

	this->gravity = gravity;
}

Particle::~Particle()
{
}

void Particle::update()
{
	float elapsedTime = g_pTimer->getTimePassed();

	// Movement
	velocity.y = velocity.y - (gravity * elapsedTime);
	origin = origin + (velocity * elapsedTime);

	// Time pass
	life -= elapsedTime;
}

vec3 Particle::getOrigin()
{
	return origin;
}

float Particle::getLife()
{
	return life;
}

void Particle::respawn(vec3 pos, vec3 dir, float lifeTime)
{
	origin = pos;
	velocity = dir;
	life = lifeTime;
}

bool Particle::alive()
{
	return (life > 0);
}
