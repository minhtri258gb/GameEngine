#ifndef EQUIPMENTMANAGER_H_
#define EQUIPMENTMANAGER_H_

#include "../object/entity/EquipmentEntity.h"


class EquipmentManager
{
public:
	EquipmentManager();
	~EquipmentManager();

	// Change data
	void add(EquipmentEntity*);

private:

	// Variable
	vector<EquipmentEntity*> listEquipment;
};

#endif
