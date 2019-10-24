#ifndef __STATICENTITY_H__
#define __STATICENTITY_H__

#include "../../../OLD/object/Entity.h"
#include "../../../engine/object/models/StaticModel.h"
#include "../../../engine/object/body/BodyBox.h"


class StaticEntity: public Entity
{
public:

	// Constructor / Destructor
	StaticEntity(StaticModel *model, BodyBox *body, vec3 origin, quat angle, float scale);
	~StaticEntity();

	// Framework
	void update();
	void render();

private:

	// Variable
	StaticModel *m_model;
	BodyBox *m_body;
};

#endif
