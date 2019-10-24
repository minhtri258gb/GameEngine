#ifndef QUADTILE_H
#define QUADTILE_H

#include "../../../Old/object/Entity.h"


class QuadData
{
public:

	// Constructor / Dstructor
	QuadData();
	~QuadData();

	// Framework
	void update();
	void render();

	// Change data
	void add(Entity*);

private:

	// Variable
	vector<Entity*> listEntity;
};

#endif
