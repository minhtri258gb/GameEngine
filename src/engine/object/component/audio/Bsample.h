#ifndef __BSAMPLE_H__
#define __BSAMPLE_H__


class Bsample
{
public:

	// Constructor
	Bsample();
	~Bsample();

	// Event
	void play(vec3*);

	// Change data
	void load(string);

private:

	// Variable
	unsigned int core, channel;
};

#endif
