#ifndef QUADTREEVISION_H_
#define QUADTREEVISION_H_

#include "../../API/OpenGL/vao/VertexBufferMonoID.h"

class QuadTreeVision
{
public:

	// Constructor / Destructor
	QuadTreeVision();
	void init(float minX, float maxX, float minZ, float maxZ);
	~QuadTreeVision();

	// Framework
	void update();
	void render();

private:

	// Variable
	VertexBufferMonoID m_vb;

};

#endif
