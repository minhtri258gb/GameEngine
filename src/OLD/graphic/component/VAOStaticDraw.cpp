
#include <glad/glad.h>

#include "../../../Main.h"
#include "VAOStaticDraw.h"


VAOStaticDraw::~VAOStaticDraw() {
	for(int i=0; i<attributes; i++)
		delete vbo[i];
	delete[] vbo;
	if(ebo)
		delete ebo;
}

void VAOStaticDraw::init(int attributes) {
	VAO::init(attributes);
	vbo = new VBOStaticDraw*[attributes];
}

void VAOStaticDraw::draw() {
	if(ebo) VAO::draw(true);
	else VAO::draw(false);
}

void VAOStaticDraw::createAttribute(int attribute, vector<vec3> data) {
	vbo[attribute] = new VBOStaticDraw();
	vbo[attribute]->bindVBO();
	vbo[attribute]->storeData(data);
	glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
	vbo[attribute]->unbind();
}

void VAOStaticDraw::createAttribute(int attribute, vector<vec2> data) {
	vbo[attribute] = new VBOStaticDraw();
	vbo[attribute]->bindVBO();
	vbo[attribute]->storeData(data);
	glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);
	vbo[attribute]->unbind();
}

//void VAOStaticDraw::createAttribute(int attribute, float* data, int attrSize, short sizeArr) {
//	vbo[attribute] = new VBOStaticDraw();
//	vbo[attribute]->bindVBO();
//	vbo[attribute]->storeData(data, sizeArr);
//	glVertexAttribPointer(attribute, attrSize, GL_FLOAT, GL_FALSE, attrSize * sizeof(float), (void*)0);
//	vbo[attribute]->unbind();
//}

void VAOStaticDraw::createIndexBuffer(vector<unsigned int> indices) {
	ebo = new EBOStaticDraw();
	ebo->bindEBO();
	ebo->storeData(indices);
	indexCount = indices.size();
}

//void VAOStaticDraw::createIndexBuffer(unsigned int* indices, short sizeArr) {
//	ebo = new EBOStaticDraw();
//	ebo->bindEBO();
//	ebo->storeData(indices, sizeArr);
//	indexCount = sizeArr/4;
//}
