#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "ParticleManager.h"
#include "Particle.h"


class Emitter {
public:

	// Static
	static ParticleManager* manager;
	static void init();
	static void cleanUp();

	// Constructor
	Emitter(int idtex, short maxParticle, float gravity, float lifeTime);
	~Emitter();

	// General
    void update();
    void render();

    // Get / Set
    void setOrigin(vec3);

protected:

private:

	// Variable
	list<Particle*> listParticle;
	int idTex;
	vec3 origin;
	float lifeTime;
};

#endif
