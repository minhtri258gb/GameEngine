#ifndef __TEXTURECUBE_H__
#define __TEXTURECUBE_H__


class TextureCube
{
public:

	// Constructor
	TextureCube();
	~TextureCube();

	// General
	void bind();

	// Change data
	void load(vector<string>);

private:

	// Variable
	unsigned int m_index;
};

#endif
