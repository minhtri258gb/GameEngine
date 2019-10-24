#ifndef __VERTEXBUFFERDYNAMIC_H__
#define __VERTEXBUFFERDYNAMIC_H__


class VertexBufferDynamic
{
public:

	// Constructor / Destructor
	VertexBufferDynamic();
	void init(int attribute);
	void storaAttribute(int attribute, int vecNum, int sizeArr);
	void storaIndex(short sizeArr);
	~VertexBufferDynamic();

	// General
	void bind();
	void draw();
	void unbind();

	// Change data
	void updateAttribute(int attribute, vector<vec2> data);
	void updateAttribute(int attribute, vector<vec3> data);
	void updateIndex(vector<unsigned int> indices);

private:

	// Variable
	unsigned int m_vao, *m_vbos, m_ebo;
	unsigned int m_nAttr, m_count;
};

#endif
