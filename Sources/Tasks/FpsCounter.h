#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/GUI.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"


class FpsCounter : public Component
{
	double	lastTime;
	int		lastfCount;
	double	fps;

public:
	FpsCounter() 
	{
		lastTime = Time::GetTime();
		lastfCount = Time::GetFrameCount();
		fps = 0;
	}

	virtual void Init(Object * pObject) {
	}

	virtual ~FpsCounter() {}

	virtual void Update() {		
		double currentTime = Time::GetTime();
		if (currentTime - lastTime > 1) {			
			int fcount = Time::GetFrameCount();
			fps = (fcount - lastfCount)/(Time::GetTime() - lastTime);
			lastfCount = fcount;
			lastTime = currentTime;
		}
		GUI::Label(0, 0, 0, 0, fps);			
	}
};
