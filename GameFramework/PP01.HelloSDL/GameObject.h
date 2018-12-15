#pragma once
#include "LoaderParams.h"
#include "SDL.h"
#include <map>

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	void SetActive(bool value) { active = value; }
	bool GetActive() { return active; }
protected:
	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}

	std::string m_textureID;
	int m_currentFrame;
	int m_currentRow;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int a = 1;
	int num;
	bool active;
};

