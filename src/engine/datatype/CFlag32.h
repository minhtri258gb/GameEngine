#ifndef __CFLAG32_H__
#define __CFLAG32_H__

namespace mt
{

typedef class CFlag32
{
public:

	// Constructor / Destructor
	CFlag32();
	CFlag32(unsigned int);
	~CFlag32();

	// Get / Set
	bool check(unsigned int);
	void setOn(unsigned int rhs);
	void setOff(unsigned int rhs);
	void setFlip(unsigned int rhs);

private:

	// Variable
	unsigned int core;

} flag;

}

#endif
