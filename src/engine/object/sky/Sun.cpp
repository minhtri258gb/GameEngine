
#include "../../../Main.h"
#include "Sun.h"


Sun::Sun(vec3 origin)
{
	m_origin = origin;

	m_origin *= -1;
	normalize(m_origin);
	light = new DirectionalLight(m_origin);
}

Sun::~Sun()
{
	delete light;
}

vec3 Sun::getOrigin()
{
	return m_origin;
}
