#include "Enemy.h"
#include "AnimatedGraphic.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	//m_velocity.setY(2);
	m_velocity.setX(5);
}

void Enemy::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	if (m_position.getX() < 0) 
	{
		m_velocity.setX(5);
	}
	else if (m_position.getX() > 1285)
	{
		//m_velocity.setX(-2);
		m_position.setX(-3);
	}

	SDLGameObject::update();
}

void Enemy::clean()
{

}