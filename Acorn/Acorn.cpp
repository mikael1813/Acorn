#include "Acorn.hpp"
#include "TextureManager.hpp"
#include "SDL.h"


Acorn::Acorn(Properties* props) : Character(props)
{
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 5, 300, SDL_FLIP_HORIZONTAL);
}

void Acorn::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Acorn::Update(float dt)
{
	m_RigidBody->Update(dt);
	//m_RigidBody->ApplyForceX(3);

	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	m_Transform->TranslateY(m_RigidBody->GetPosition().Y);


	m_Animation->Update();
}

void Acorn::Clean()
{
	TextureManager::GetInstance()->Clean();
}
