
#define IMPORT_ENGINE
#include "../../Main.h"

#include "Manager.h"


Manager::Manager()
{
	StaticModel::u_manager = &m_modelmanager;
	AnimModel::u_manager = &m_modelmanager;
}

void Manager::init()
{
	m_modelmanager.init();
	modelshader.init();
}

Manager::~Manager()
{
}
