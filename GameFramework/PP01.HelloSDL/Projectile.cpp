#include "Projectile.h"
#include "InputHandler.h"

Projectile::Projectile(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Projectile::draw()
{
	if (active)
	{
		if (drawbullet)
		{
			SDLGameObject::draw();
		}
	}

}

void Projectile::update()
{
	if (active)
	{
		if (drawbullet)
		{
			m_position.setX(m_position.getX() + 5);

			m_currentFrame = int(((SDL_GetTicks() / 100) % 1));

			if (m_position.getX() >= 1285)
			{
				drawbullet = false;
			}
		}
	}
	handleInput();
	SDLGameObject::update();
}

void Projectile::clean()
{

}

void Projectile::shoot(float x, float y)
{
	if (drawbullet)
	{
		return;
	}
	m_position.setX(x);
	m_position.setY(y + 60);
	drawbullet = true;
}

void Projectile::handleInput()
{

}