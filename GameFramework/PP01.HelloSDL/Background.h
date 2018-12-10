#pragma once
#include "SDLGameObject.h"

class Background : public SDLGameObject
{
private:
	int bgX = 0, bgY = 0;
	int m_numFrames = 1;

public:
	Background(const LoaderParams* pParams); 
	virtual void draw();
	virtual void update();
	virtual void clean();
};