#ifndef __SUN_H__
#define __SUN_H__

#include "../light/DirectionalLight.h"

class Sun
{
public:

	// Variable
	DirectionalLight *light;

	// Constructor
	Sun(vec3 origin);
	~Sun();

	// General
	vec3 getOrigin();

private:

	// Variable
	vec3 m_origin;

};

#endif
