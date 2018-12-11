#include "Projectile.h"
#include "InputHandler.h"

Projectile::Projectile(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	//m_velocity.setY(2);
	m_velocity.setX(5);
}

void Projectile::draw()
{
	SDLGameObject::draw();
}

void Projectile::update()
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

void Projectile::clean()
{

}