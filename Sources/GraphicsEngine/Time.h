#pragma once


class Time
{
public:

	static void Update();

	/*
	* @brief The time in seconds since the run of the application.
	*/
	static double GetTime()
	{
		return time;
	}

	/*
	* @brief The time in seconds have been needed to render the last frame.
	*/
	static double GetDeltaTime()
	{
		return deltaTime;
	}

	/*
	* @brief The number of frames that have been rendered.
	*/
	static int GetFrameCount()
	{
		return frameCount;
	}

private:

	static bool isInited;

	static double startClock;

	static double curFrameTime;
	static double prevFrameTime;

	static double time;
	static double deltaTime;

	static int frameCount;
};
