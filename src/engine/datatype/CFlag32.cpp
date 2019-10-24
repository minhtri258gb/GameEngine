#include "CFlag32.h"

namespace mt
{

CFlag32::CFlag32()
{
	// unsigned char flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
	core = 0;
}

CFlag32::CFlag32(unsigned int value)
{
	core = value;
}

CFlag32::~CFlag32()
{
}

bool CFlag32::check(unsigned int mark)
{
	return core & (1 << mark);
}

void CFlag32::setOn(unsigned int mark)
{
	core |= (1 << mark);
}

void CFlag32::setOff(unsigned int mark)
{
	core &= ~(1 << mark);
}

void CFlag32::setFlip(unsigned int mark)
{
	core ^= (1 << mark);
}

}
