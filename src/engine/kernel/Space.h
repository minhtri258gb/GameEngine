#ifndef __SPACE_H__
#define __SPACE_H__

#include "quadtree/QuadTree.h"
#include "../object/sky/SkyBox.h"
#include "../object/terrain/Terrain.h"
#include "../../OLD/object/Entity.h"


class Space
{
public:

	// Variable
	SkyBox skybox;
	Terrain terrain;

	// Constructor / Destructor
	Space();
	void init();
	~Space();

	// Framework
	void update();
	void render();

	// General
	void add(Entity*);

	// Get / Set
	string getMapName();
	void setMapName(string);

private:

	// Variable
	string m_mapname;
	QuadTree *m_root;
	array<QuadTree*, 9> m_area;

	// Get / Set
	QuadTree* getNode(unsigned short level, vec2 position);
};

#endif
