#include "PlayState.h"
#include "TextureManager.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "SDLGameObject.h"
#include "Item.h"
#include "Background.h"
#include "Enemy.h"
using namespace std;
const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (dynamic_cast<SDLGameObject*>(earth)->GetCount() == 3 && !spawn_item )
	{
		m_gameObjects[E_Item]->SetActive(true);		
		spawn_item = true;
	}

	for (int i = 0; i < m_gameObjects.size(); i++) 
	{
		if(m_gameObjects[i]->GetActive())
		m_gameObjects[i]->update();
		
	}
	
	if (spawn_item) {
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[E_Player]), dynamic_cast<SDLGameObject*>(m_gameObjects[E_Item])))
		{
			// ÃÑ ½ò¼öÀÖÀ½!
			player = new Player(new LoaderParams(500, 100, 105, 130, "astronaut_gun"));
			//±×¸®°í
			item->SetActive(false);
		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[E_Player]), dynamic_cast<SDLGameObject*>(m_gameObjects[E_Pluto])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());

		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[E_Player]), dynamic_cast<SDLGameObject*>(m_gameObjects[E_Mars])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[E_Player]), dynamic_cast<SDLGameObject*>(m_gameObjects[E_Earth])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}
		
	}
	else
	{
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[E_Player]), dynamic_cast<SDLGameObject*>(m_gameObjects[E_Pluto])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());

		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[E_Player]), dynamic_cast<SDLGameObject*>(m_gameObjects[E_Mars])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[E_Player]), dynamic_cast<SDLGameObject*>(m_gameObjects[E_Earth])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}
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
		if (m_gameObjects[i]->GetActive())
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
	if (!TheTextureManager::Instance()->load("assets/mars.png", "mars", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/earth.png", "earth", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/item.png", "item", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/backgroundscroll.png", "background", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/astronaut_gun.png", "astronaut_gun", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	srand((unsigned int)time(0));

	player = new Player(new LoaderParams(500, 100, 105, 130, "astronaut"));
	pluto = new Enemy(new LoaderParams(1285, rand() % 620 + 1, 70, 70, "pluto"));
	mars = new Enemy(new LoaderParams(1285, rand() % 620 + 1, 80, 80, "mars"));
	earth = new Enemy(new LoaderParams(1285, rand() % 620 + 1, 100, 100, "earth"));
	Background* background = new Background(new LoaderParams(-5, 0, 5120, 720, "background"));
	item = new Item(new LoaderParams(1285, (rand() % 620) + 1, 50, 50, "item"));
	item->SetActive(false);

	//////////////////////////////////////////
	m_gameObjects.push_back(background);	//
	m_gameObjects.push_back(player);		//
	m_gameObjects.push_back(earth);			//
	m_gameObjects.push_back(mars);			//
	m_gameObjects.push_back(pluto);			//
	m_gameObjects.push_back(item);			//
	//////////////////////////////////////////

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

