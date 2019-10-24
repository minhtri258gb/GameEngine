#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../API/bass/Audio.h"
#include "../API/enet/Network.h"
#include "../API/bullet/World.h"


class System
{
public:

	// Variable
	World world;
	Audio audio;
	Network network;

	// Constructor / Destructor
	System();
	void init();
	~System();

	// General
	void log(string);
	void error(string);
	bool probability(unsigned int n);
	unsigned int rand(unsigned int n);
	int range(int, int);

	// Get / Set
	bool isRun();

	// Change data
	void exit();

	// Framework

	// Event

private:

	// Variable
	bool m_mainloop;
	std::mt19937 rd;
};

#endif
