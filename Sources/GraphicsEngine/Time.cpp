#include "Time.h"
#include <time.h>


bool Time::isInited = false;

double Time::startClock = 0.0;

double Time::curFrameTime = 0.0;
double Time::prevFrameTime = 0.0;

double Time::time = 0.0;
double Time::deltaTime = 0.0;

int Time::frameCount = 0;


void Time::Update()
{
	if (false == isInited)
	{
		startClock	= clock();
		isInited	= true;
	}

	curFrameTime = (clock() - startClock) / CLOCKS_PER_SEC;

	time		= curFrameTime;
	deltaTime	= curFrameTime - prevFrameTime;

	prevFrameTime = curFrameTime;

	++frameCount;
}
