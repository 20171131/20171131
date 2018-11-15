#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SDLGameObject.h"
#include <vector>
#include <map>


class Game {
private:

	Game() {}
	static Game* s_pInstance;

	SDL_Window * m_pWindow;
	SDL_Renderer* m_pRenderer;


	bool m_bRunning;
	int m_currentFrame;

	std::vector<GameObject*> m_gameObjects;

public:

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	~Game() {}
	SDL_Renderer* getRenderer()const { return m_pRenderer; }
	bool init(const char* title, int xpos, int ypos,
		int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	bool running() { return m_bRunning; }
	void clean();




};	typedef Game TheGame;
