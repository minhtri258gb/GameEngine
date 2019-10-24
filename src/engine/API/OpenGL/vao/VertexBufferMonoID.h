#ifndef __VERTEXBUFFERMONOID_H__
#define __VERTEXBUFFERMONOID_H__

#include "VertexBuffer.h"


class VertexBufferMonoID: public VertexBuffer
{
public:

	// Constructor / Destructor
	VertexBufferMonoID();
	~VertexBufferMonoID();

	// General
	void draw();

	// Change data
	void setIndex(vector<unsigned int>);

private:

	// Variable
	unsigned int m_count, m_ebo;
};

#endif
