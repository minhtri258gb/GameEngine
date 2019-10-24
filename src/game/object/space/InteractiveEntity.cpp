
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/file/CFGFile.h"
#include "InteractiveEntity.h"


InteractiveEntity::InteractiveEntity(string modelname, string modelext, vec3 origin, int angle, float scale)
{
	m_origin = origin;
	m_angle = quat(angle, vec3(0,1,0)); // FIXME
	m_scale = scale;
	m_model = NULL;
	m_controller = NULL;

	load(modelname, modelext);
}

InteractiveEntity::~InteractiveEntity()
{
	delete m_controller;
}

void InteractiveEntity::update()
{
	m_controller->update(&m_origin, &m_angle);
}

void InteractiveEntity::render()
{
	m_model->render(m_origin, m_angle, m_scale);
}

void InteractiveEntity::load(string modelname, string modelext)
{

//	m_model = engine.space.modelManager.precache(modelname, modelext);
//
//	// Load info
//	CFGFile *fCFG = new CFGFile("res/models/" + modelname + "/info.cfg");
//
//	fCFG->select("[mesh]");
//	if(fCFG->get("cullface") == "false")
//		m_model->setCullface(false);
//
//	fCFG->select("[texture]");
//	m_model->setTextureAtlas((short) fCFG->get("atlas").toInteger());
//
//	fCFG->select("[body]");
//	Vec3 boundingbox;
//	fCFG->get("size").parse("%f %f %f", &boundingbox.x, &boundingbox.y,
//			&boundingbox.z);
//	boundingbox *= m_scale;
//	m_controller = new RigidController(boundingbox, m_origin, m_angle, this);
//
//	delete fCFG;
}
