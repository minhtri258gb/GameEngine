
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "Sound.h"


Sound::Sound(vec3* origin)
{
	sample = NULL;
	this->origin = origin;
}

Sound::~Sound()
{
	delete sample;
}

void Sound::play()
{
	sample->play(origin);
}

void Sound::load(string filename)
{
	sample = new Bsample();
	sample->load(filename);
}

//void Sound::pause() {
//	channel->pause();
//	status = PAUSE;
//}
