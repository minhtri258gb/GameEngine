
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../../engine/kernel/Timer.h"
extern Timer *g_pTimer;

#include "../../../engine/math/Math.h"
extern Math *g_pMath;

#include "Sprite.h"


SpriteManager *Sprite::manager;


void Sprite::init()
{
	manager = new SpriteManager();
	manager->init();
}

void Sprite::cleanUp()
{
}

Sprite::Sprite(int idTex, float roundTime)
{
	this->idTex = idTex;
	this->roundTime = curTime = roundTime;
}

Sprite::~Sprite()
{
	//dtor
}

void Sprite::update()
{
	curTime -= g_pTimer->getTimePassed();
	if(curTime <= 0)
		curTime = roundTime;
}

void Sprite::render()
{
	manager->shader->use();

	// view model matrix
	mat4 viewmodel = g_pMath->viewmodel(g_pGraphic->getViewMat(), vec3(30582, 4070, 26888), 1000.0f);
	manager->shader->loadMatViewModel(viewmodel);

	// Texture
	int numOfRow = manager->texture->getNumRow(idTex);
	vec4 offsetTex;
	float atlasPrecess((1.0f - (curTime / roundTime)) * (numOfRow * numOfRow - 1));
	int index = (int) floor(atlasPrecess);
	offsetTex.x = (index % numOfRow) * 1.0f / numOfRow;
	offsetTex.y = (index / numOfRow) * 1.0f / numOfRow;
	index++;
	offsetTex.z = (index % numOfRow) * 1.0f / numOfRow;
	offsetTex.w = (index / numOfRow) * 1.0f / numOfRow;

	manager->shader->loadOffsetTex(offsetTex);
	manager->shader->loadBlendFactor(fmod(atlasPrecess, 1.0f));
	manager->shader->loadNumOfRow(numOfRow);

	manager->texture->bind(idTex);

	manager->vao->bindVAO();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	manager->vao->unbind();
}

