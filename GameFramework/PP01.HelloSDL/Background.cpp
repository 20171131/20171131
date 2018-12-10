#include "Background.h"

Background::Background(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(5);
}

void Background::draw()
{
	SDLGameObject::draw();
}

void Background::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	//if (m_position.getX() >= 0)
	//{
	//	m_velocity.setX(5);
	//}
	//else if (m_position.getX() > 1280)
	//{
	//	m_position.setX(-1280);
	//}

	if (m_position.getX() < 0)
	{
		m_velocity.setX(5);
	}
	else if (m_position.getX() > 2000)
	{
		//m_velocity.setX(-2);
		m_position.setX(-3);
	}

	SDLGameObject::update();
}

void Background::clean()
{

}