#ifndef DEBUGOBJECT_H_
#define DEBUGOBJECT_H_

#include "../../engine/object/debug/CoordinateSystem.h"
#include "../../engine/object/debug/DebugShader.h"

enum
{
	UNKNOW = 0, COORDINATE_SYSTEM = 1 << 0, BODY_PHYSIC = 1 << 1, SOUND_POSITION = 1 << 2
};

class DebugObject
{
public:

	// Variable
	DebugShader *shader;

	// Constructor / Destructor
	DebugObject();
	void init(int flag = UNKNOW);
	~DebugObject();

	// Framework
	void update();
	void render();

	// Change data

private:

	// Variable
	int flag;
	CoordinateSystem *m_coordinateSystem;
};

#endif
