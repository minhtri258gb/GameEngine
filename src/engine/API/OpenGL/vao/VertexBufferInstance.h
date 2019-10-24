#ifndef __VERTEXBUFFERINSTANCE_H__
#define __VERTEXBUFFERINSTANCE_H__


class VertexBufferInstance
{
public:

	// Constrcutor / Destructor
	VertexBufferInstance();
	void init(int numAttribute, int lenInstance, int numInstance);
	virtual ~VertexBufferInstance();

	// Framework
	void draw(int count);

	// General
	void bind();
	void unbind();

	// Change data
	void setVertices();
	void storaAttribute();
	void updateBuffer(float *data, int bufferSize);

private:

	// Variable
	int numAttribute;
	unsigned int m_vao, m_vbo1, m_vbo2;
};

#endif
