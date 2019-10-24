#ifndef WEAPON_H
#define WEAPON_H

#include "../models/Model.h"


class Weapon {
public:

	// Constructor
	Weapon();
	~Weapon();

private:

	// Variable
	Model* model;
};

#endif
