#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__

#include "Light.h"


class SpotLight : public Light
{
public:

	// Constructor / Destructor
	SpotLight();
	virtual ~SpotLight();

private:

	// Variable
	vec3 m_origin, m_direct;
};

#endif
