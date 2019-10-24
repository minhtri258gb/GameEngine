#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
public:

	// Constructor
	Entity();
	virtual ~Entity();

	// Framework
	virtual void update();
	virtual void render();

	// Get / Set
	vec3 *getPOrigin();
	vec3 getOrigin();

protected:

	// Variable
	vec3 m_origin;
	quat m_angle;
	float m_scale;
};

#endif
