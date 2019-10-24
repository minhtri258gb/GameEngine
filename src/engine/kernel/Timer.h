#ifndef __TIMER_H__
#define __TIMER_H__


class Timer
{
public:

	// Constructor
	Timer();

	// General
	void init();
	void sync();

	// Get / Set
	void setFPSLimit(int);
	float getFPS();
	float getTimePassed();

private:

	// Variable	
	double frameTimeLimit;
	double lastTime;
	double elapsedTime;
};

#endif
