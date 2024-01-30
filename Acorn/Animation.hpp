#pragma once

#include "SDL.h"
#include <string>

class Animation {
public:
	Animation();

	void Update();
	void Draw(float x, float y, int spritWidth, int spriteHeight);
	void SetProps(std::string textureId, int spriteRow, int FrameCount, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int m_SpriteRow, m_SpriteFrame;
	int	m_FrameCount, m_AnimationSpeed;
	std::string m_TextureId;
	SDL_RendererFlip m_Flip;
};