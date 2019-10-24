#ifndef __LOADER_H__
#define __LOADER_H__

#include "load/Precache.h"


class Loader
{
public:

	// Variable
	Precache precache;

	// Constructor
	Loader();
	~Loader();

	// General
	void setting();
	void keybind();
	void map();
	void entity();
	void stora();
};

#endif
