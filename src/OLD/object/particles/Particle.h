#ifndef PARTICLE_H
#define PARTICLE_H


class Particle {
public:

	// Constructor
	Particle(float gravity);
	~Particle();

	// General
	void update();

	// Get / Set
	vec3 getOrigin();
	float getLife();

	// Check
	bool alive();

	// Change data
	void respawn(vec3 pos, vec3 dir, float lifeTime);

private:

	// Variable
	vec3 origin, velocity;
	float gravity, life;
};

#endif
