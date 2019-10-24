#ifndef __VERTEXBUFFERMULTIID_H__
#define __VERTEXBUFFERMULTIID_H__

#include "VertexBuffer.h"


class VertexBufferMultiID: public VertexBuffer
{
public:

	// Constructor / Destructor
	VertexBufferMultiID();
	~VertexBufferMultiID();

	// General
	void draw(unsigned int);

	// Get / Set
	unsigned int getNumPart();

	// Change data
	void setIndex(vector<unsigned int>);
	void setPart(vector<unsigned int>);

private:

	// Variable
	vector<unsigned int> m_ebo;
	vector<unsigned int> m_part;
};

#endif
