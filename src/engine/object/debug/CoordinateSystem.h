#ifndef __COORDINATESYSTEM_H__
#define __COORDINATESYSTEM_H__

#include "../../API/OpenGL/vao/VertexBufferMonoID.h"


class CoordinateSystem
{
public:

	// Constructor / Destructor
	CoordinateSystem();
	void init();
	~CoordinateSystem();

	// Framework
	void render();

	// Get / Set
	mat4 getTransform();

private:

	// Variable
	VertexBufferMonoID m_vb;
};

#endif
