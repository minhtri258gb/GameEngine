
/**
 * QuadData is component of QuadTree left (level 1) has information
 */

#include <glm/glm.hpp>

#define IMPORT_ENGINE

#include "../../../Main.h"
#include "QuadData.h"

QuadData::QuadData()
{
}

QuadData::~QuadData()
{
	for(Entity *ent : listEntity)
		delete ent;
}

void QuadData::update()
{
	for(Entity *ent : listEntity)
		ent->update();
}

void QuadData::render()
{
	for(Entity *ent : listEntity)
		ent->render();
}

void QuadData::add(Entity *ent)
{
	listEntity.push_back(ent);
}
