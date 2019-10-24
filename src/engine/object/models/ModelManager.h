#ifndef __MODELMANAGER_H__
#define __MODELMANAGER_H__


class ModelManager;
#include "StaticModel.h"
#include "AnimModel.h"


class ModelManager
{
public:

	// Variable
	unsigned int m_idProgramS, m_viewLocS, m_modelLocS;
	unsigned int m_idProgramA, m_viewLocA, m_modelLocA;

	// Constructor
	ModelManager();
	void init();
	~ModelManager();

	// General
	void add(StaticModel*);
	void add(AnimModel*);

private:

	// Variable
	vector<StaticModel*> m_listModelS;
	vector<AnimModel*> m_listModelA;
};

#endif
