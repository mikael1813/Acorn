#include "Acorn.hpp"
#include "TextureManager.hpp"
#include "SDL.h"
#include "Input.hpp"
#include "Camera.hpp"
#include "CollisionHandler.hpp"


Acorn::Acorn(Properties* props) : Character(props)
{
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;

	m_IsGrounded = false;
	m_IsJumping = false;

	m_Collider = new Collider();
	m_Collider->SetBuffer(0, 0, 0, 0);

	m_RigidBody = new RigidBody();
	//m_RigidBody->SetGravity(0.5f);

	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 5, 300);
}

void Acorn::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->GetBox();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Acorn::Update(float dt)
{
	m_Animation->SetProps(m_TextureID, 0, 5, 300);

	//m_RigidBody->UnSetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		m_RigidBody->ApplyForceX(-3);
		// can add animation here
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		m_RigidBody->ApplyForceX(3);
		// can add animation here
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
		if (m_IsGrounded) {

			m_RigidBody->ApplyForceY(-20, 5);
			// can add animation here

			m_IsJumping = true;
			m_IsGrounded = false;
		}
		else {
			m_IsJumping = false;
		}

	}

	if (m_IsGrounded) {
		m_RigidBody->SetGravity(0);
		m_RigidBody->UnSetMomentumY();
	}
	else {
		m_RigidBody->SetGravity(1.0f);
	}


	// move on X axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())) {
		m_Transform->X = m_LastSafePosition.X;
	}

	//  move on Y axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())) {
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
		m_RigidBody->UnSetMomentumY();
	}
	else {
		m_IsGrounded = false;
	}


	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update();
}

void Acorn::Clean()
{
	TextureManager::GetInstance()->Clean();
}
