
#include <bass/bass.h>

#include "../../../../Main.h"
#include "Bsample.h"


Bsample::Bsample()
{
}

Bsample::~Bsample()
{
}

void Bsample::play(vec3 *position)
{
//	qwe "play" zxc
//	if(BASS_ChannelIsActive(channel))
//		return;
//	qwe "play" zxc

	BASS_3DVECTOR pos;
	pos.x = position->x;
	pos.y = position->y;
	pos.z = position->z;
	BASS_ChannelSet3DPosition(channel, &pos, NULL, NULL);
	BASS_Apply3D();

	BASS_ChannelPlay(channel, true);
}

void Bsample::load(string filename)
{
	core = BASS_SampleLoad(false, filename.c_str(), 0, 0, 1,
			BASS_SAMPLE_OVER_DIST | BASS_SAMPLE_3D);

	BASS_SAMPLE sampleInfo;
	BASS_SampleGetInfo(core, &sampleInfo);
	sampleInfo.volume = 20;
	sampleInfo.mindist = 8;
	sampleInfo.maxdist = 1024;
	BASS_SampleSetInfo(core, &sampleInfo);

	channel = BASS_SampleGetChannel(core, false);
}
