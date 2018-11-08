#include"SDL.h"

class Game
{
	SDL_Texture* m_pTexture; // the new SDL_Texture variable
	SDL_Rect m_sourceRectangle; // 원본 사각형 
	SDL_Rect m_destinationRectangle; // 대상 사각형 

public:
	Game() {}
	~Game() {}
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();
	bool running() { return m_bRunning; }

private:
	SDL_Window * m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
};