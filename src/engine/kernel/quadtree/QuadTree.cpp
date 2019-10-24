
/**
 * QuadNode is core of QuadTree include pointer to parent, child, neighbor, ...
 *
 * Level leaf is 1
 */

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../View.h"
extern View *g_pView;

#include "../Space.h"
extern Space *g_pSpace;

#include "QuadTree.h"

#define CELLSPACE (1<<8)
#define LEVELTEXTURE 9


QuadTree::QuadTree(QuadTree* parent, vec2 origin, unsigned char level)
{
	m_parent = parent;

	for(short i = 0; i < 4; i++)
		m_children[i] = m_neighbor[i] = NULL;

    m_origin = origin;
    m_level = level;
    m_flags = 0;

    if(level > 1)
    {
		data = NULL;
        split();
    }
    else data = new QuadData();
}

/**
 * Index of neighbor:
 *			0
 * 		1		2
 * 			3
 **/
void QuadTree::initNeighbor(QuadTree* n0, QuadTree* n1, QuadTree* n2, QuadTree* n3)
{
    m_neighbor[0] = n0;
    m_neighbor[1] = n1;
    m_neighbor[2] = n2;
    m_neighbor[3] = n3;

	// Neighbor outter of children
    QuadTree *noc1, *noc2;

	if(m_children[0])
	{
		noc1 = n0 ? n0->m_children[2] : NULL;
		noc2 = n1 ? n1->m_children[1] : NULL;
		m_children[0]->initNeighbor(noc1, noc2, m_children[1], m_children[2]);
	}

	if(m_children[1])
	{
		noc1 = n0 ? n0->m_children[3] : NULL;
		noc2 = n2 ? n2->m_children[0] : NULL;
		m_children[1]->initNeighbor(noc1, m_children[0], noc2, m_children[3]);
	}

	if(m_children[2])
	{
		noc1 = n1 ? n1->m_children[3] : NULL;
		noc2 = n3 ? n3->m_children[0] : NULL;
		m_children[2]->initNeighbor(m_children[0], noc1, m_children[3], noc2);
	}

	if(m_children[3])
	{
		noc1 = n2 ? n2->m_children[2] : NULL;
		noc2 = n3 ? n3->m_children[1] : NULL;
		m_children[3]->initNeighbor(m_children[1], m_children[2], noc1, noc2);
	}
}

QuadTree::~QuadTree()
{
	if(data)
		delete data;

	for(short i=0; i<4; i++)
        if(m_children[i])
            delete m_children[i];
}

void QuadTree::update()
{
	// if(m_origin.x >= engine.space.terrain.m_maxlength || m_origin.y >= engine.space.terrain.m_maxwidth)
	// {
	// 	m_visible = false;
	// 	m_render = true;
	// 	return;
	// }

	vec3 playerPos = g_pView->getPosition();
	int halfsize = 1 << (m_level - 1);

	int midX = m_origin.x + halfsize;
	int midZ = m_origin.y + halfsize;
	int midY = g_pSpace->terrain.getHeightGrid(midX, midZ);

	if(!g_pView->frustumCulling.isSphereInFrustum(vec3(midX * CELLSPACE, midY, midZ * CELLSPACE), (1<<m_level)*CELLSPACE))
	{
		m_visible = false;
		m_render = true;
		return;
	}
	else m_visible = true;

	// Level of Detail
	int maxDis = (int) abs(playerPos.x/CELLSPACE - midX);
	int tempDis = (int) abs(playerPos.z/CELLSPACE - midZ);
	if(tempDis > maxDis) maxDis = tempDis;
	tempDis = (int) (abs(playerPos.y - midY) / CELLSPACE);
	if(tempDis > maxDis) maxDis = tempDis;

	if(maxDis > (1 << (m_level+1)) || m_level == 2)
		m_render = true;
	else
	{
		m_render = false;
		for(short i=0; i<4; i++)
			if(m_children[i])
				m_children[i]->update();
	}
}

//void QuadNode::update()
//{
//	// Level of Detail
//	Vec3 playerPos = engine.view.getPosition();
//	int maxDis = abs((int)playerPos.x - midX);
//	int tempDis = abs((int)playerPos.z - midZ);
//	if(tempDis > maxDis) maxDis = tempDis;
//	tempDis = abs((int)playerPos.y - midY);
//	if(tempDis > maxDis) maxDis = tempDis;
//
////	if(m_level == 2)
//	if(maxDis > (1 << (m_level + 1)) || m_level == 2)
//		m_render = true;
//	else
//	{
//		m_render = false;
//
//		for(short i = 0; i < 4; i++)
//			if(children[i])
//				children[i]->update();
//	}
//}

void QuadTree::updateBase()
{
	if(data)
		data->update();
	else
		for(short i = 0; i < 4; i++)
			if(m_children[i])
				m_children[i]->updateBase();
}

void QuadTree::render()
{
	if(!m_visible)
		return;

    if(m_render)
    {
		if(m_visible)
		{
			mt::flag patch;
			for(short i=0; i<4; i++)
				if(m_neighbor[i] && m_neighbor[i]->m_parent->m_render)
					patch.setOn(i);
			g_pSpace->terrain.render(m_origin, m_level, patch);
		}
	}
    else
	{
		for(short i=0; i<4; i++)
			if(m_children[i])
				m_children[i]->render();
	}
}

//void QuadNode::render()
//{
//	if(!m_visiable)
//		return;
//
//	if(m_render)
//	{
//		flag patch;
//		for(short i=0; i<4; i++)
//			if(m_neighbor[i] && m_neighbor[i]->m_parent->m_render)
//				patch.setOn(i);
//
////		Terrain *t = &engine.space.terrain;
////		t->render(m_origin, 1 << m_level, patch);
//	}
//	else
//		for(short i = 0; i < 4; i++)
//			if(children[i])
//				children[i]->render();
//}

void QuadTree::renderBase()
{
//	if(!m_visible)
//		return;

	if(data)
		data->render();
	else
		for(short i = 0; i < 4; i++)
			if(m_children[i])
				m_children[i]->renderBase();
}

QuadTree* QuadTree::getChildren(int index)
{
	return m_children[index];
}

QuadTree* QuadTree::getNeighbor(int index)
{
	return m_neighbor[index];
}

unsigned char QuadTree::getLevel()
{
	return m_level;
}

vec2 QuadTree::getOrigin()
{
	return m_origin;
}

/**
 * Index of children:
 *		0	1
 * 		2	3
 **/
void QuadTree::split()
{
	float minX = m_origin.x;
	float minZ = m_origin.y;
	float midX = minX + (1 << (m_level - 1));
	float midZ = minZ + (1 << (m_level - 1));

	m_children[0] = new QuadTree(this, vec2(minX, minZ), m_level - 1);
	m_children[1] = new QuadTree(this, vec2(midX, minZ), m_level - 1);
	m_children[2] = new QuadTree(this, vec2(minX, midZ), m_level - 1);
	m_children[3] = new QuadTree(this, vec2(midX, midZ), m_level - 1);
}
