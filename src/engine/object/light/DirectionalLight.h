#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#include "Light.h"


class DirectionalLight : public Light
{
public:

	// Constructor / Destructor
	DirectionalLight(vec3 direct);
	virtual ~DirectionalLight();

	// General
	vec3 getDirect();

private:

	// Variable
	vec3 m_direct;
};

#endif
