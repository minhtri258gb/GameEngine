
#include "../../Main.h"

#include "../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "Timer.h"


Timer::Timer()
{
	frameTimeLimit = 1.0 / 60.0f;
	lastTime = 0.0;
	elapsedTime = 0.0;
}

void Timer::init()
{
	lastTime = g_pGraphic->getTime();
}

void Timer::setFPSLimit(int value)
{
	frameTimeLimit = 1.0 / value;
}

float Timer::getFPS()
{
    return (elapsedTime) ? int(1.0/elapsedTime) : 0;
}

void Timer::sync()
{
	double nextTime = frameTimeLimit + lastTime;
	while(g_pGraphic->getTime() < nextTime) { } // SLEEP
	double curTime = g_pGraphic->getTime();
    elapsedTime = curTime - lastTime;
    lastTime = curTime;
}

float Timer::getTimePassed()
{
    return elapsedTime;
}
