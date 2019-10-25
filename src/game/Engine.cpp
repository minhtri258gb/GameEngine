
#define DEBUG

#include "../Main.h"
#include "../OLD/object/particles/Emitter.h"
#include "../OLD/object/sprites/Sprite.h"
#include "Engine.h"

#include "../engine/object/models/StaticModel.h"


Graphic *g_pGraphic;
System *g_pSystem;
Command *g_pCommand;
Timer *g_pTimer;
Manager *g_pManager;
Space *g_pSpace;
View *g_pView;
Loader *g_pLoader;
Math *g_pMath;


Engine::Engine()
{
	m_loader = new Loader();

	// m_stora = new Stora();
	// m_font = new Font();
	// m_equipmentManager = new EquipmentManager();
	m_mainPlayer = new MainPlayer();
	// m_myEntity = new MyEntity();
	// m_debugObject = new DebugObject();

	// General global pointer
	g_pGraphic = &m_graphic;
	g_pSystem = &m_system;
	g_pCommand = &m_command;
	g_pTimer = &m_timer;
	g_pManager = &m_manager;
	g_pSpace = &m_space;
	g_pView = &m_view;
	g_pLoader = m_loader;
	g_pMath = &m_math;
}

Engine::~Engine()
{
	// delete m_debugObject;
	delete m_mainPlayer;
	// delete m_equipmentManager;
	// delete m_font;
	// delete m_stora;

	delete m_loader;
	
	// delete Sprite::manager->texture;
	// Emitter::cleanUp();
	// Sprite::cleanUp();

	g_pGraphic = NULL;
	g_pSystem = NULL;
	g_pCommand = NULL;
	g_pTimer = NULL;
	g_pManager = NULL;
	g_pSpace = NULL;
	g_pView = NULL;
	g_pLoader = NULL;
	g_pMath = NULL;
}

int Engine::launch()
{
	init();
	while(m_system.isRun())
		framework();
	
	return 0; // TODO error code
}

void Engine::init()
{
	// Load
	m_loader->setting();
	m_loader->keybind();

	// Init system
	m_graphic.init();
	m_system.init();
	m_timer.init();
	m_manager.init();
	m_space.init();

	// Other Object Init
	// Sprite::init();
	// Emitter::init();
	// SpriteTexture *texture = new SpriteTexture();
	// Emitter::manager->texture = texture;
	// Sprite::manager->texture = texture;
	// m_font->init();
	// m_font->changeText(0, "", vec2(0.005f, 0.97f), 0.5f, vec3(0.3f, 0.7f, 0.9f));
	// m_font->changeText(1, "This is sample text", vec2(0.02f, 0.035f), 1.0f, vec3(0.5f, 0.8f, 0.2f));
	
	m_loader->map();

	m_mainPlayer->init();
	// m_myEntity->init();
	// m_debugObject->init(COORDINATE_SYSTEM); // COORDINATE_SYSTEM

	// Load again
	m_loader->entity();
	// m_loader->stora();

	// Build objects

	// Add objects into world and stora
	// m_stora->init();
	// m_space.add(m_myEntity);
}

void Engine::framework()
{
	// Update
	m_command.update();
	m_graphic.update();
	m_system.world.update();
	m_mainPlayer->update();
	m_view.update(); // after mainPlayer
	m_space.update();
	// m_myEntity->update();
	// m_system.audio.update();
	// m_debugObject->update();

	// Render
	m_graphic.render();
	// m_myEntity->render();
	m_space.render();

	// m_font->setText(0, "FPS: %.2f", m_timer.getFPS());
	// m_font->render();

	// m_debugObject->render();

	// sync
	m_graphic.sync();
	m_timer.sync();
}

void cmd_exit()
{
	g_pSystem->exit();
}
