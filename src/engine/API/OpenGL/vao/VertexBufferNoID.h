#ifndef __VERTEXBUFFERNOID_H__
#define __VERTEXBUFFERNOID_H__

#include "VertexBuffer.h"


class VertexBufferNoID: public VertexBuffer
{
public:

	// Constructor / Destructor
	VertexBufferNoID();
	~VertexBufferNoID();

	// General
	void draw();

	// Get / Set
	void setCountVertex(unsigned int);

private:

	// Variable
	unsigned int m_count;
};

#endif
