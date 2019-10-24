#ifndef MUSIC_H
#define MUSIC_H

//#include "../../engine/audio/component/Fmusic.h"


class Music {
public:

	// Constructor
	Music();
	~Music();

	// General
//	void update();

	// Event
	void play();
//	void start(bool force);
//	void pause();

	// Change data
	void load(string filename);

private:

	// Variable
//	Fmusic* core;
//	AUDIO_STATUS status;
};

#endif
