#ifndef __SOUND_H__
#define __SOUND_H__

#include "../../../engine/API/bass/Audio.h"
#include "../../../engine/object/component/audio/Bsample.h"


class Sound
{
public:

	// Constructor
	Sound(vec3* origin);
	~Sound();

	// General
//	void update();
	void play();
//
//	// Event
//	void start(bool force);
//	void pause();

//	// Change data
	void load(string filename);

private:

	// Variable
	Bsample* sample;
	vec3* origin;
};

#endif
