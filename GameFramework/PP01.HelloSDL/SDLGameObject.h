#pragma once
#include "Vector2D.h"
#include <map>
#include "GameObject.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

protected:
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

};