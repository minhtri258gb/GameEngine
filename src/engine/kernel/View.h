#ifndef __VIEW_H__
#define __VIEW_H__

#include "../../OLD/math/FrustumCulling.h"


class View
{
public:

	// Variable
	FrustumCulling frustumCulling;

	// Constructor / Destructor
	View();
	~View();

	// General
	void update();

	// Event
	void processMouseMovement(double xoffset, double yoffset);

	// Get / Set
	int getFOV();
	void setFOV(int);
	int getNear();
	void setNear(int);
	int getFar();
	void setFar(int);
	quat getQuat();
	vec3 getPosition();
	void setPosition(vec3);
	vec3 getVeclook();

private:

	// Variable
	int m_fov, m_nearLimit, m_farLimit;
	quat m_quat;
	vec3 m_origin, m_veclook;
};

#endif
