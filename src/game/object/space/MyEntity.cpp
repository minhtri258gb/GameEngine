
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "MyEntity.h"

//#define EMITTER_TEST
//#define SPRITE_TEST
#define ASSIMP_TEST
// #define AUDIO_TEST


MyEntity::MyEntity()
{
	m_origin = vec3(330, 3400, 256);

	m_emitter = NULL;
	m_sprite = NULL;
	m_music = NULL;
	m_sound = NULL;
}

MyEntity::~MyEntity()
{
	#ifdef EMITTER_TEST
	delete m_emitter;
	#endif // EMITTER_TEST

	#ifdef SPRITE_TEST
	delete m_sprite;
	#endif // SPRITE_TEST

	#ifdef AUDIO_TEST
	delete m_music;
	delete m_sound;
	#endif // AUDIO_TEST
}

void MyEntity::init()
{
	#ifdef SPRITE_TEST
	int idTex = Sprite::manager->texture->precache("fire");
	m_sprite = new Sprite(idTex, 5.0f);
	#endif // SPRITE_TEST

	#ifdef EMITTER_TEST
	idTex = Emitter::manager->texture->precache("cosmic");
	m_emitter = new Emitter(idTex, 50, 5, 1.0f);
	m_emitter->setOrigin(Vec3(29054, 3504, 26103));
	#endif // EMITTER_TEST

	#ifdef AUDIO_TEST
	m_music = new Music();
	m_music->load("res/sound/media/invtro94.s3m");
//
	m_sound = new Sound(&m_origin);
	m_sound->load("res/sound/carhorn.wav");
//
//	engine->myEntity->m_music->start(true);
	#endif // AUDIO_TEST
}

void MyEntity::update()
{
	#ifdef SPRITE_TEST
	m_sprite->update();
	#endif // SPRITE_TEST

	#ifdef EMITTER_TEST
	m_emitter->update();
	#endif // EMITTER_TEST

	#ifdef ASSIMP_TEST
	// m_mdl->update();
	#endif // ASSIMP_TEST

	#ifdef AUDIO_TEST
//	m_music->update();
//	m_sound->update();
	#endif // AUDIO_TEST
}

void MyEntity::render()
{
	#ifdef SPRITE_TEST
	m_sprite->render();
	#endif // SPRITE_TEST

	#ifdef EMITTER_TEST
	m_emitter->render(); // Some time crash
	#endif // EMITTER_TEST

	#ifdef AUDIO_TEST
//	m_music->play();
//	m_sound->play();
	#endif // AUDIO_TEST
}


void cmd_test1()
{
	engine.m_myEntity->m_sound->play();
}

void cmd_test2() {
//	engine->myEntity->m_sound->pause();
}
