#ifndef VAOMULTISTATIC_H
#define VAOMULTISTATIC_H

#include "VBOStaticDraw.h"
#include "EBOStaticDraw.h"


class VAOMultiStatic
{
public:

	// Constructor
	VAOMultiStatic();
	~VAOMultiStatic();

	// General
	void init();
	void draw(int meshID);
	void bind();
	void unbind();

	// Get / Set
	unsigned int getNumIndiences();

	// Change data
	void addAttribute(vector<vec3>);
	void addAttribute(vector<vec2>);
	void addIndexBuffer(vector<unsigned int>);

private:

	// Variable
	unsigned int m_ID;
	unsigned int m_atributes;
	vector<VBOStaticDraw*> m_vbos;
	vector<vector<unsigned int>> m_ebos;
};

#endif
