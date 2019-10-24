#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "Light.h"


class PointLight : public Light
{
public:

	// Constructor / Destructor
	PointLight();
	virtual ~PointLight();

private:

	// Variable
	vec3 m_origin;
};

#endif
