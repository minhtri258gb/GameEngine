
#include "../../Main.h"
#include "Entity.h"


Entity::Entity()
{
	m_scale = 1.0f;
}

Entity::~Entity()
{
}

void Entity::update()
{
	cout << "[Entity::update] do nothing" << endl;
}

void Entity::render()
{
	cout << "[Entity::render] do nothing" << endl;
}

vec3* Entity::getPOrigin()
{
	return &m_origin;
}

vec3 Entity::getOrigin()
{
	return m_origin;
}
