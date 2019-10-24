
#include <glm/glm.hpp>

#include "../../../Main.h"
#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(vec3 direct)
{
	m_direct = direct;
}

DirectionalLight::~DirectionalLight()
{
}

vec3 DirectionalLight::getDirect()
{
	return m_direct;
}
