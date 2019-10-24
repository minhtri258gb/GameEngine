
#define LOW_QUALITY 0

#include <bass/bass.h>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../kernel/System.h"
extern System *g_pSystem;

#include "../../kernel/View.h"
extern View *g_pView;

#include "Audio.h"

#if LOW_QUALITY
	#define MIXRATE 22050
#else
#define MIXRATE 44100
#endif // LOW_QUALITY

//#define MAXCHANNEL 32 // 64

Audio::Audio()
{
}

Audio::~Audio()
{
	BASS_Stop();
	BASS_Free();
}

void Audio::init()
{
	// Check version
	if (HIWORD(BASS_GetVersion()) != BASSVERSION)
	{ // v2.4
		g_pSystem->error("[Audio] Incorrect version BASS loaded!");
		return;
	}

	// Variable reference
//	listenerPos = engine.view->getPositionPointer();
//	listenerFront = engine.view->getVecLookPointer();

	// Device

	BASS_SetConfig(BASS_CONFIG_DEV_DEFAULT, 1);
	BASS_DEVICEINFO di;
	int a, device = -1;
	for (a = 1; BASS_GetDeviceInfo(a, &di); a++)
	{
//		std::cout << "Driver name: " << di.name << std::endl;
		device = a;
	}

	// Init
	if (!BASS_Init(device, MIXRATE, BASS_DEVICE_3D, 0, NULL))
	{
		g_pSystem->error("[Audio] Can't initialize device");
		return;
	}

	// Set parameters
	BASS_Set3DFactors(ACTUAL_UNIT, ACTUAL_UNIT, ACTUAL_UNIT);
//    FSOUND_SetSFXMasterVolume(255); // default 255
//    FSOUND_3D_SetDistanceFactor(ACTUAL_UNIT);
//    FSOUND_3D_SetRolloffFactor(1.0f); // default 1.0f

	BASS_Start();
}

void Audio::update()
{
	vec3 position = g_pView->getPosition();
	vec3 veclook = g_pView->getPosition();

	BASS_3DVECTOR pos, vel, front, top;
	pos.x = position.x;
	pos.y = position.y;
	pos.z = position.z;
	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;
	front.x = veclook.x;
	front.y = veclook.y;
	front.z = veclook.z;
	top.x = 0.0f;
	top.y = 1.0f;
	top.z = 0.0f;

	BASS_Set3DPosition(&pos, &vel, &front, &top);

	BASS_Apply3D();
}

float getMasterVolume()
{
	return BASS_GetVolume();
}

void setMasterVolume(float volume)
{ // 0.0 - 1.0
	BASS_SetVolume(volume);
}

unsigned int getSampleVolume()
{
	return BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE);
}

void setSampleVolume(unsigned int volume)
{ // 0 - 10000
	BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, volume);
}

unsigned int getStreamVolume()
{
	return BASS_GetConfig(BASS_CONFIG_GVOL_STREAM);
}

void setStreamVolume(unsigned int volume)
{ // 0 - 10000
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, volume);
}

unsigned int getMusicVolume()
{
	return BASS_GetConfig(BASS_CONFIG_GVOL_MUSIC);
}

void setMusicVolume(unsigned int volume)
{ // 0 - 10000
	BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, volume);
}
