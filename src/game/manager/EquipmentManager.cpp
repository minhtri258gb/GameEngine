
#include "../../Main.h"

class AnimModel;
#include "EquipmentManager.h"


EquipmentManager::EquipmentManager()
{
	// TODO Auto-generated constructor stub

}

EquipmentManager::~EquipmentManager()
{
	// TODO Auto-generated destructor stub
}

void EquipmentManager::add(EquipmentEntity* ent)
{
	listEquipment.push_back(ent);
}
