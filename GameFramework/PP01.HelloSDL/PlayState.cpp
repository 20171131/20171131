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
#include "Projectile.h"
#include "iostream"
const std::string PlayState::s_playID = "PLAY";


/////////행성이랑 부딪히면 행성이 사라지는거 아이템처럼 똑같이 하려했는데
void PlayState::update()
{
	if (dynamic_cast<SDLGameObject*>(earth)->GetCount() == 3 && !spawn_item )
	{
		m_gameObjects[ITEM]->SetActive(true);	
		
		spawn_item = true;
	}

	for (int i = 0; i < m_gameObjects.size(); i++) 
	{
		if (m_gameObjects[i]->GetActive())
		{
			m_gameObjects[i]->update();
		}
	}
	
	if (spawn_item) 
	{
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER]), dynamic_cast<SDLGameObject*>(m_gameObjects[ITEM])))
		{
			//스프라이트 바꾸기
			/*GameObject* player1 = new Player(new LoaderParams(500, 100, 105, 130, "astronaut_gun"));
			m_gameObjects.push_back(player1);*/
			item->SetActive(false);
			bullet->SetActive(true);
			
		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER]), dynamic_cast<SDLGameObject*>(m_gameObjects[PLUTO]))&&pluto->GetActive())
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());

		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER]), dynamic_cast<SDLGameObject*>(m_gameObjects[MARS])) && mars->GetActive())
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER]), dynamic_cast<SDLGameObject*>(m_gameObjects[EARTH])) && earth->GetActive())
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}	
		
		//////////////////////////////아이템 먹고 난후 ??행성이랑 플레이어랑 충돌체크하는 부분이요?여기 위에가 아이템 활성화된 이후고 아래는 
		else if (bullet->GetActive())
		{
			if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[BULLET]), dynamic_cast<SDLGameObject*>(m_gameObjects[PLUTO])))
			{
				pluto->SetActive(false);
				
			}
			else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[BULLET]), dynamic_cast<SDLGameObject*>(m_gameObjects[MARS])))
			{
				mars->SetActive(false);

			}
			else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[BULLET]), dynamic_cast<SDLGameObject*>(m_gameObjects[EARTH])))
			{
				earth->SetActive(false);

			}
		}
	}
	else
	{
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER]), dynamic_cast<SDLGameObject*>(m_gameObjects[PLUTO])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());

		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER]), dynamic_cast<SDLGameObject*>(m_gameObjects[MARS])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}
		else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[PLAYER]), dynamic_cast<SDLGameObject*>(m_gameObjects[EARTH])))
		{
			TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		}
		///////////
		else if (bullet->GetActive())
		{
			if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[BULLET]), 
				dynamic_cast<SDLGameObject*>(m_gameObjects[PLUTO])))
			{
				pluto->SetActive(false);
				pluto->clean();
			}
			else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[BULLET]),
				dynamic_cast<SDLGameObject*>(m_gameObjects[MARS])))
			{
				mars->SetActive(false);
				mars->clean();
			}
			else if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[BULLET]), 
				dynamic_cast<SDLGameObject*>(m_gameObjects[EARTH])))
			{
				earth->SetActive(false);
				earth->clean();
			}
		}
		
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(new PauseState());
	}

	if (TheInputHandler::Instance()->getMouseButtonState(0))
	{
		float x = c_player->getPosition().getX() + 55;
		float y = c_player->getPosition().getY();
		c_projectile->shoot(x, y);
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
		{
			m_gameObjects[i]->draw();
		}
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
	if (!TheTextureManager::Instance()->load("assets/bullet.png", "bullet", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	srand((unsigned int)time(0));

	player = new Player(new LoaderParams(500, 100, 105, 130, "astronaut_gun"));
	pluto = new Enemy(new LoaderParams(1285, rand() % 620 + 1, 70, 70, "pluto"));
	mars = new Enemy(new LoaderParams(1285, rand() % 620 + 1, 80, 80, "mars"));
	earth = new Enemy(new LoaderParams(1285, rand() % 620 + 1, 100, 100, "earth"));
	Background* background = new Background(new LoaderParams(-5, 0, 5120, 720, "background"));
	item = new Item(new LoaderParams(1285, (rand() % 620) + 1, 50, 50, "item"));
	item->SetActive(false);
	bullet = new Projectile(new LoaderParams(100, 600, 30, 15, "bullet"));
	bullet->SetActive(false);

	//////////////////////////////////////////
	m_gameObjects.push_back(background);	//0
	m_gameObjects.push_back(player);		//1
	m_gameObjects.push_back(earth);			//2 
	m_gameObjects.push_back(mars);			//
	m_gameObjects.push_back(pluto);			//
	m_gameObjects.push_back(item);			//
	m_gameObjects.push_back(bullet);		//
	//////////////////////////////////////////


	this->c_player = (Player*)player;
	this->c_projectile = (Projectile*)bullet;

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

	TheTextureManager::Instance()->clearFromTextureMap("player");
	TheTextureManager::Instance()->clearFromTextureMap("pluto");
	TheTextureManager::Instance()->clearFromTextureMap("mars");
	TheTextureManager::Instance()->clearFromTextureMap("earth");

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

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}

