#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "../engine/API/OpenGL/Graphic.h"
#include "../engine/kernel/System.h"
#include "../engine/kernel/Command.h"
#include "../engine/kernel/Timer.h"
#include "../engine/kernel/Manager.h"
#include "../engine/kernel/Space.h"
#include "../engine/kernel/View.h"
#include "../engine/kernel/Loader.h"
#include "../engine/math/Math.h"

#include "object/Stora.h"
// #include "../OLD/object/font/Font.h"
// #include "manager/EquipmentManager.h"
#include "object/player/MainPlayer.h"
#include "object/space/MyEntity.h"
#include "object/DebugObject.h"

#define ACTUAL_UNIT 40.0f


class Engine
{
public:

	// Variable
	// Stora *m_stora;
	MainPlayer *m_mainPlayer;
	// MyEntity *m_myEntity;
	// EquipmentManager *m_equipmentManager;
	// Font *m_font;
	// DebugObject *m_debugObject;

	// General
	int launch();

	// Constructor
	Engine();
	~Engine();

private:

	// Variable
	Graphic m_graphic;
	System m_system;
	Command m_command;
	Timer m_timer;
	Manager m_manager;
	Space m_space;
	View m_view;
	Loader *m_loader;
	Math m_math;

	// General
	void init();
	void framework();
};

#endif
