#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>


class Texture {
public:
	unsigned int ID;

	// Constructor
	Texture();
	Texture(unsigned int ID);
	~Texture();

	// General
	void load(string filename);
	void loadCube(string listtexture[6]);
	void bindTex();
	void bindTexCube();

	// Get / Set

private:
};

#endif
