#pragma once
#include"GameState.h"

class MenuState : public GameState
{
protected:
	std::vector<GameObject*> m_gameObjects;

private:
	static const std::string s_menuID;
	static MenuState* s_pInstance;

	static void s_menuToPlay();
	static void s_exitFromMenu();

public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }

	static MenuState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new MenuState();
			return s_pInstance;
		}
		return s_pInstance;
	}
};