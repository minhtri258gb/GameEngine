#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "../object/models/ModelManager.h"
#include "../object/models/StaticModel.h"
#include "../object/models/AnimModel.h"


class Manager
{
public:

	// Constructor / Destructor
	Manager();
	void init();
	~Manager();

private:

	// Variable
	ModelManager m_modelmanager;

};

#endif
