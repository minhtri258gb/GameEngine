#ifndef MYENTITY_H
#define MYENTITY_H

#include "../../../OLD/object/Entity.h"
#include "../../../OLD/object/particles/Emitter.h"
#include "../../../OLD/object/sprites/Sprite.h"
#include "../../../OLD/object/sound/Music.h"
#include "../../../OLD/object/sound/Sound.h"


class MyEntity : public Entity {
public:

	// Variable
	Emitter* m_emitter;
	Sprite* m_sprite;
	Music* m_music;
	Sound* m_sound;

	// Constructor
	MyEntity();
	~MyEntity();

	// General
	void init();
	void update();
	void render();
};

#endif
