
#include "../../../Main.h"
#include "Precache.h"

Precache::Precache()
{
	//ctor
}

Precache::~Precache()
{
	for(MTMDFile *f : m_staticmodel)
		delete f;
}

void Precache::precacheModel()
{
}

void Precache::precacheSprite()
{
}

void Precache::precacheSound()
{
}

void Precache::precacheMusic()
{
}

list<MTMDFile*> Precache::getListWeapons()
{
	return m_staticmodel;
}

void Precache::entity(string type, MTMDFile *file)
{
	if(type == "static")
		m_staticmodel.push_back(file);
	else if(type == "animation")
	{
//		m_storaWeapons.push_back(file);
	}
	else if(type == "weapon")
	{
//		m_storaWeapons.push_back(file);
	}
}
