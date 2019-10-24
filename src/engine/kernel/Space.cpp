/**
 * QuadTree is main include root and more handle on QuadNode
 *
 * HASH TAG
 *  - terrain 256 level 8: #LEVEL8
 */

#define IMPORT_ENGINE
#include "../../Main.h"

#include "View.h"
extern View *g_pView;

#include "Space.h"

#define CELLSPACE (1<<8)


Space::Space()
{
	m_root = NULL;
}

void Space::init()
{
	m_root = new QuadTree(NULL, vec2(), 8); // #LEVEL8
	m_root->initNeighbor(NULL, NULL, NULL, NULL);
}

Space::~Space()
{
	delete m_root;
}

/**
 * Update area:	5 <- 1    7
 * 			  V 2    0    3 ^
 * 				6    4 -> 8
 */
void Space::update()
{
	// Check area
	vec3 origin = g_pView->getPosition();
	m_area[0] = getNode(1, vec2(origin.x, origin.z));
	m_area[1] = m_area[0]->getNeighbor(0);
	m_area[2] = m_area[0]->getNeighbor(1);
	m_area[3] = m_area[0]->getNeighbor(2);
	m_area[4] = m_area[0]->getNeighbor(3);
	m_area[5] = m_area[1] ? m_area[1]->getNeighbor(1) : NULL;
	m_area[6] = m_area[2] ? m_area[2]->getNeighbor(3) : NULL;
	m_area[7] = m_area[3] ? m_area[3]->getNeighbor(0) : NULL;
	m_area[8] = m_area[4] ? m_area[4]->getNeighbor(2) : NULL;

	// Update tree
	m_root->update();

	// Base update
	for(QuadTree* node : m_area)
		if(node)
			node->updateBase();
}

/**
 * Render area:		3
 * 				2	3
 * 			1	2	3
 * 				2	3
 * 					3
 */
void Space::render()
{
	// Skybox render
	skybox.render();

	// Terrain render
	terrain.renderPre();
	m_root->render();
	terrain.renderPost();

	// Base render
	for(QuadTree* node : m_area)
		if(node)
			node->renderBase();
}

void Space::add(Entity *ent)
{
	vec3 origin = ent->getOrigin();
	QuadTree *node = getNode(1, vec2(origin.x, origin.z));
	node->data->add(ent);
}

string Space::getMapName()
{
	return m_mapname;
}

void Space::setMapName(string name)
{
	m_mapname = name;
}

QuadTree* Space::getNode(unsigned short level, vec2 position)
{
	position.x /= CELLSPACE;
	position.y /= CELLSPACE;

	QuadTree *curNode = m_root;
	while(curNode->getLevel() > level)
	{
		int halfsize = 1 << (curNode->getLevel() - 1);
		float midX = curNode->getOrigin().x + halfsize;
		float midZ = curNode->getOrigin().y + halfsize;

		int index = 0;
		if(position.y > midZ) index = 2;
		if(position.x > midX) index++;

		curNode = curNode->getChildren(index);
	}
	return curNode;
}
