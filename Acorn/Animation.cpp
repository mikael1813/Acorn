#include "Animation.hpp"
#include "TextureManager.hpp"

Animation::Animation()
{

}

void Animation::Update()
{
	m_SpriteFrame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spritWidth, int spriteHeight)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureId, x, y, spritWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(std::string textureId, int spriteRow, int FrameCount, int animationSpeed, SDL_RendererFlip flip)
{
	m_TextureId = textureId;
	m_SpriteRow = spriteRow;
	m_FrameCount = FrameCount;
	m_AnimationSpeed = animationSpeed;
	m_Flip = flip;
}
