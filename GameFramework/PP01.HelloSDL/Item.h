#pragma once
#include "SDLGameObject.h"
#include "Enemy.h"

class Item : public SDLGameObject
{
public:
	Item(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_numFrames = 1;
	const int default_speed = -8;
	int current_speed;
};