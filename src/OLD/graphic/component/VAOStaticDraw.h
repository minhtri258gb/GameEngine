#ifndef VAOSTATICDRAW_H
#define VAOSTATICDRAW_H

#include "VAO.h"
#include "VBOStaticDraw.h"
#include "EBOStaticDraw.h"


class VAOStaticDraw : public VAO {
public:

	// Constructor
	~VAOStaticDraw();

	// General
	void init(int attributes);
	void draw();

	// Change data
	void createAttribute(int attribute, vector<vec3> data);
	void createAttribute(int attribute, vector<vec2> data);
//	void createAttribute(int attribute, float* data, int attrSize, short sizeArr);
	void createIndexBuffer(vector<unsigned int> indices);
//	void createIndexBuffer(unsigned int* indices, short sizeArr);

private:
	VBOStaticDraw** vbo;
	EBOStaticDraw* ebo;
};

#endif
