
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/file/CFGFile.h"

#include "StaticEntity.h"


StaticEntity::StaticEntity(StaticModel *model, BodyBox *body, vec3 origin, quat angle, float scale)
{
	m_model = model;
	m_body = body;
	m_origin = origin;
	m_angle = angle;
	m_scale = scale;

	body->setUser(this);
}

StaticEntity::~StaticEntity()
{
	delete m_body;
}

void StaticEntity::update()
{
//	m_body->update(&m_origin, &m_angle);
}

void StaticEntity::render()
{
	m_model->render(vec3(m_origin.x,m_origin.y,m_origin.z), m_angle, m_scale);
}

//void StaticEntity::load(String modelname)
//{
//	// Load model
//	m_model = engine.modelManager->precache(modelname, "obj");
//
//	// Load info
//	CFGFile *fCFG = new CFGFile("res/models/" + modelname + "/info.cfg");
//
//	fCFG->select("[mesh]");
//	if (fCFG->get("cullface") == "false")
//		m_model->setCullface(false);
//
//	fCFG->select("[texture]");
//	m_model->setTextureAtlas((short) fCFG->get("atlas").toInteger());
//
//	fCFG->select("[body]");
//	Vec3 boundingbox;
//	fCFG->get("size").parse("%f %f %f", &boundingbox.x, &boundingbox.y, &boundingbox.z);
//	boundingbox *= m_scale;
//	m_controller = new RigidController(boundingbox, m_origin, m_angle, this, true);
//
//	delete fCFG;
//}
