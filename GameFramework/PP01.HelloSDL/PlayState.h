#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
#include <time.h>
#include <iostream>
#include <cstdlib>

class GameObject;
enum Object
{
	PLAYER = 1,
	EARTH = 2,
	MARS = 3,
	PLUTO = 4,
	ITEM = 5,
	BULLET = 6
};

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_playID; }

	static PlayState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new PlayState();
			return s_pInstance;
		}
		return s_pInstance;
	}
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

private:
	static const std::string s_playID;
	static PlayState* s_pInstance;

	bool spawn_item = false; 

	std::vector<GameObject*> m_gameObjects;

	clock_t start, now;
	GameObject* player;
	GameObject* pluto;
	GameObject* mars;
	GameObject* earth;
	GameObject* item;
	GameObject* bullet;

	class Projectile* c_projectile;
	class Player* c_player;
};