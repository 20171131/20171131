#pragma once
#include "GameState.h"
#include <iostream>

class GameObject;

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_pauseID; }

private:
	static void s_pauseToMain();
	static void s_resumePlay();
	//static PauseState* s_pInstance;
	static const std::string s_pauseID;
	std::vector<GameObject*> m_gameObjects;
};