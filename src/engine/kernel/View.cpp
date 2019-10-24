
#include <glm/gtc/matrix_transform.hpp>

#define IMPORT_ENGINE
#include "../../Main.h"

#include "../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../kernel/View.h"
extern View *g_pView;

#include "../../OLD/math/MathView.h"
#include "View.h"

#define EYEHIGHT 64.0f


View::View()
{
	m_fov = 60;
	m_nearLimit = 1;
	m_farLimit = 56756;
	m_quat.y = 1;
}

View::~View()
{
}

void View::update()
{
	m_veclook = vec3(	2.0f * (m_quat.x*m_quat.z - m_quat.y*m_quat.w),
						2.0f * (m_quat.y*m_quat.z + m_quat.x*m_quat.w),
						1.0f - 2.0f * (m_quat.x*m_quat.x + m_quat.y*m_quat.y));

	g_pGraphic->setViewMat(lookAt(m_origin, m_origin + m_veclook, vec3(0,1,0)));
	frustumCulling.update();
}

void View::processMouseMovement(double xoffset, double yoffset)
{
	const float sensitivity = 0.002f;
	float angleQ = xoffset * sensitivity;
	m_quat = cross(m_quat, angleAxis(angleQ, vec3(0,1,0)));

	angleQ = yoffset * sensitivity;
	quat tmp = cross(angleAxis(angleQ, vec3(1,0,0)), m_quat);
	if(tmp.x * tmp.x + tmp.z * tmp.z < 0.48f)
		m_quat = tmp;

	normalize(m_quat);
}

int View::getFOV()
{
	return m_fov;
}

void View::setFOV(int value)
{
	m_fov = value;
}

int View::getNear()
{
	return m_nearLimit;
}

void View::setNear(int value)
{
	m_nearLimit = value;
}

int View::getFar()
{
	return m_farLimit;
}

void View::setFar(int value)
{
	m_farLimit = value;
}

quat View::getQuat()
{
	return m_quat;
}

vec3 View::getPosition()
{
	return m_origin;
}

void View::setPosition(vec3 pos)
{
	m_origin = pos;
}

vec3 View::getVeclook()
{
	return m_veclook;
}

void cmd_debugorigin()
{
	vec3 p = g_pView->getPosition();
	cout << "origin: " << p.x << ", " << p.y - EYEHIGHT << ", " << p.z << endl;
	cout << "angle: " << (int) (yaw(g_pView->getQuat()) * 57.29577951f) << endl; // TODO fix here
}
