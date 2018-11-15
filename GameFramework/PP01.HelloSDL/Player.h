#pragma once
#include "SDL.h"
#include "SDLGameObject.h"
#include <map>

class Player :public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	void handleInput();

};
