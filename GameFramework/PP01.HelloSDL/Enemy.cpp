#include "Enemy.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams), default_speed(-8)
{
	m_velocity.setX(-(rand() % 4) + 3);
	current_speed = default_speed;
}

void Enemy::draw()
{
	if(active)
	SDLGameObject::draw();
}

void Enemy::update()
{
	////////// TODO : 이거이거해야되;ㅁ 이거 안되고 에러남 개박친 내일하ㅔㅁ
	if (active)
	{
		m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

		if (m_position.getX() < 1290)
		{
			m_velocity.setX(current_speed);
		}
		if (m_position.getX() <= -5)
		{
			++count;
			m_position.setY(rand() % 620 + 1);
			m_position.setX(rand() % 1000 + 1290);
			current_speed += -(rand() % 4) + 3;

			if (current_speed > default_speed + 2)
				current_speed = default_speed;
		}

		SDLGameObject::update();
	}
}

void Enemy::clean()
{

}