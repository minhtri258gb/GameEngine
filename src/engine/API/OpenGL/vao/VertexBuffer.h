#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

class VertexBuffer
{
public:

	// Constrcutor / Destructor
	VertexBuffer();
	void init();
	virtual ~VertexBuffer();

	// General
	void bind();
	void unbind();

	// Change data
	void addAttribute(vector<vec3>);
	void addAttribute(vector<vec2>);

private:

	// Variable
	unsigned int m_vao;
	list<unsigned int> m_vbos;
};

#endif
