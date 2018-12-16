#include "Item.h"

Item::Item(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(-(rand() % 4) + 3);
	current_speed = default_speed;
}

void Item::draw()
{
	if (active)
	{
		SDLGameObject::draw();
	}
}

void Item::update()
{
	if (active)
	{
		m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

		if (m_position.getX() < 1290)
		{
			m_velocity.setX(current_speed);
		}
		if (m_position.getX() <= -1280)
		{
			m_position.setY(rand() % 620 + 1);
			m_position.setX(3000);
			current_speed += -(rand() % 4) + 3;

			if (current_speed > default_speed + 2)
				current_speed = default_speed;
		}

		SDLGameObject::update();
	}
}

void Item::clean()
{

}