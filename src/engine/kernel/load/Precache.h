#ifndef PRECACHE_H_
#define PRECACHE_H_

#include "../../file/MTMDFile.h"

class Precache
{
public:

	// Constructor
	Precache();
	~Precache();

	// General
	void precacheModel();
	void precacheSprite();
	void precacheSound();
	void precacheMusic();

	// Get / Set
	list<MTMDFile*> getListWeapons();

	// Change data
	void entity(string type, MTMDFile *file);

private:

	// Variable
	list<MTMDFile*> m_staticmodel;
};

#endif
