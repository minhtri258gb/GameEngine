#ifndef __TEXTURE2DPACK_H__
#define __TEXTURE2DPACK_H__

class Texture2DPack
{
public:

	// Constructor / Destructor
	Texture2DPack();
	~Texture2DPack();

	// General
	void bind();

	// Change data
	void loadAdd(string);

private:

	// Variable
	vector<unsigned int> m_indexs;
};

#endif
