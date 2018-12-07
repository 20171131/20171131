#include "PlayState.h"
#include "TextureManager.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "SDLGameObject.h"
#include <iostream>
#include <cstdlib>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++) 
	{
		m_gameObjects[i]->update();
	}

	if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[1]), dynamic_cast<SDLGameObject*>(m_gameObjects[2])))
	{
		TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
	}
	else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[1]), dynamic_cast<SDLGameObject*>(m_gameObjects[3])))
	{
		TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(new PauseState());
	}

	now = clock();
	clock_t frameTime = now - start;
	std::cout << "frameTime : " << (frameTime / 1000.0f) << " sec" << std::endl;
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/astronaut.png", "astronaut", TheGame::Instance()->getRenderer())) 
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/pluto.png", "pluto", TheGame::Instance()->getRenderer())) 
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/background.png", "background", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	srand((unsigned int)time(0));
	int v_random = rand() % 600 + 1;

	GameObject* player = new Player(new LoaderParams(500, 100, 105, 130, "astronaut"));
	GameObject* enemy = new Enemy(new LoaderParams(-5, v_random, 100, 100, "pluto"));
	v_random = rand() % 430 + 1;
	GameObject* enemy1 = new Enemy(new LoaderParams(-5, v_random, 100, 100, "pluto"));
	GameObject* SDLgameobject = new SDLGameObject(new LoaderParams(0, 0, 1280, 720, "background"));

	m_gameObjects.push_back(SDLgameobject);
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy);
	m_gameObjects.push_back(enemy1);

	std::cout << "entering PlayState\n";

	start = clock();

	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("helicopter");
	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}

