
#include <glad/glad.h> // FIXME

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../../engine/kernel/System.h"
extern System *g_pSystem;

#include "../../../engine/kernel/View.h"
extern View *g_pView;

#include "../../../engine/math/Math.h"
extern Math *g_pMath;

#include "Emitter.h"

#define PROBABILITY 1


ParticleManager *Emitter::manager;


void Emitter::init()
{
	manager = new ParticleManager();
	manager->init();
}

void Emitter::cleanUp()
{
	delete manager;
}

bool distanceParticle(Particle *&first, Particle *&second)
{
	vec3 viewPos = g_pView->getPosition();
	float dis1 = (first->getOrigin() - viewPos).length();
	float dis2 = (second->getOrigin() - viewPos).length();
	return dis1 > dis2;
}

Emitter::Emitter(int idTex, short maxParticle, float gravity, float lifeTime)
{
	for(short i = 0; i < maxParticle; i++)
		listParticle.push_back(new Particle(gravity));

	this->idTex = idTex;
	this->lifeTime = lifeTime;
}

Emitter::~Emitter()
{
	for(Particle *particle : listParticle)
		delete particle;
}

void Emitter::update()
{
	bool spawn = true;
	for(Particle *particle : listParticle)
	{
		if(particle->alive())
			particle->update();
		else if(spawn)
		{
			spawn = false;
			particle->respawn(origin, vec3(g_pSystem->range(-100, 100), g_pSystem->range(200, 800), g_pSystem->range(-100, 100)),
//								Vec3(0, 0, 0),
								lifeTime);
			particle->update();
		}
	}

	listParticle.sort(distanceParticle);
}

void Emitter::render()
{
	if(!g_pView->frustumCulling.isSphereInFrustum(origin, 20.0f))
		return;

	manager->shader->use();

	g_pGraphic->setBlend(true, 2);
	g_pGraphic->setDepth(false);

	manager->texture->bind(idTex);

	int numOfRow = manager->texture->getNumRow(idTex);
	manager->shader->loadNumOfRow(numOfRow);

	int maxParticle = listParticle.size();
	int bufferSize = maxParticle * manager->INSTANCE_DATA_LENGTH;
	vector<float> buffer;
	short countParticleAlive = 0;
	for(Particle *particle : listParticle)
	{
		if(!particle->alive())
			continue;

		countParticleAlive++;

		// Transform
		mat4 viewmodel = g_pMath->viewmodel(g_pGraphic->getViewMat(), particle->getOrigin(), 100.0f);
		for(int i = 0; i < 16; i++)
			buffer.push_back(viewmodel[i/4][i%4]);

		// Tex coord
		float atlasPrecess((1.0f - (particle->getLife() / lifeTime)) * (numOfRow * numOfRow - 1));
		int index = (int) floor(atlasPrecess);
		buffer.push_back((index % numOfRow) * 1.0f / numOfRow);
		buffer.push_back((index / numOfRow) * 1.0f / numOfRow);
		index++;
		buffer.push_back((index % numOfRow) * 1.0f / numOfRow);
		buffer.push_back((index / numOfRow) * 1.0f / numOfRow);
		buffer.push_back(fmod(atlasPrecess, 1.0f));
	}
	glBindVertexArray(manager->vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);

	glBindBuffer(GL_ARRAY_BUFFER, manager->vboID2);
	glBufferData(GL_ARRAY_BUFFER, bufferSize * 4, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize * 4, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, countParticleAlive);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glBindVertexArray(0);

	g_pGraphic->setBlend(false);
	g_pGraphic->setDepth(true);
}

void Emitter::setOrigin(vec3 origin)
{
	this->origin = origin;
}
