#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

class Texture2D
{
public:

	// Constructor / Destructor
	Texture2D();
	Texture2D(string);
	~Texture2D();

	// General
	void bind();

	// Change data
	void load(string);

private:

	// Variable
	unsigned int m_index;
};

#endif
