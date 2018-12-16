#include "GameObject.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

void GameObject::draw()
{
	//TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, m_pRenderer);
}

void GameObject::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void GameObject::clean()
{
	
}