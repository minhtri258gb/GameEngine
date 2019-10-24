#ifndef __VERTEXBUFFERMAIN_H__
#define __VERTEXBUFFERMAIN_H__


class VertexBufferMain
{
public:

	// Constructor / Destructor
	VertexBufferMain();
	void init();
	~VertexBufferMain();

	// General
	void bind();
	void unbind();
	void drawArrays(int start, int count);
	void drawElements(int count, unsigned int *indices);

	// Change data
	void addAttribute(vector<vec3>);
	void addAttribute(vector<ivec3>);
	void addAttribute(vector<vec2>);
	void setIndex(vector<unsigned int>);

private:

	// Variable
	unsigned int m_vao;
	list<unsigned int> m_vbos;
	unsigned int m_ebo;
};

#endif
