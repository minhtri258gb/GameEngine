#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "../../../Old/object/Entity.h"
#include "QuadData.h"


class QuadTree
{
public:

	// Variable
	QuadData *data;

	// Constructor / Destructor
	QuadTree(QuadTree* parent, vec2 origin, unsigned char level);
    void initNeighbor(QuadTree* n0, QuadTree* n1, QuadTree* n2, QuadTree* n3);
	~QuadTree();

	// Framework
	void update();
		void updateBase();
	void render();
		void renderBase();

	// Get / Set
	QuadTree* getChildren(int);
	QuadTree* getNeighbor(int);
	unsigned char getLevel();
	vec2 getOrigin();

private:

	// Variable
	QuadTree* m_parent;
	QuadTree* m_children[4];
	QuadTree* m_neighbor[4];

	vec2 m_origin;
    bool m_render;
    bool m_visible;
    unsigned char m_flags;
    unsigned char m_level;

	// General
    void split();

};

#endif
