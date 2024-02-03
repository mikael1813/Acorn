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

	m_TimeToWait = 0;
	m_FallingTime = 0;

	m_Bounciness = 0.2f;
	m_TimePressedSpace = 0.0f;

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

	if (m_TimeToWait > 0) {
		m_TimeToWait -= dt;

		// idle animation

		return;
	}

	SDL_Log("Delta time is %f", dt);

	//m_RigidBody->UnSetForce();

	bool PressedA = Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT);
	bool PressedD = Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT);

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
		m_PressedSpace = true;
		m_TimePressedSpace += dt;
	}

	//if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && m_IsGrounded) {
	//	m_RigidBody->ApplyForceX(-3);
	//	// can add animation here
	//}

	//if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && m_IsGrounded) {
	//	m_RigidBody->ApplyForceX(3);
	//	// can add animation here
	//}

	if (m_PressedSpace && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded) {

		float scalar = 1.0f, scalar2 = 1.0f;
		
		if (m_TimePressedSpace < 10) {
			scalar = 0.5f;
			scalar2 = 1.25f;
		}
		else if (m_TimePressedSpace < 20) {
			scalar = 0.75f;
		}

		float vertical_force = -20 * scalar;
		float horizontal_force = 10 * scalar * scalar2;

		if (PressedA && PressedD) {
			m_RigidBody->ApplyForceY(vertical_force, 5);
		}
		else if (PressedA) {
			m_RigidBody->ApplyForce(Vector2D(-horizontal_force, vertical_force), 5);
		}
		else if (PressedD) {
			m_RigidBody->ApplyForce(Vector2D(horizontal_force, vertical_force), 5);
		}
		else {
			m_RigidBody->ApplyForceY(vertical_force, 5);
		}

		m_TimePressedSpace = 0.0f;
		m_PressedSpace = false;
	}


	// move on X axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	CollisionType collision_x = CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox());

	if (collision_x != CollisionType::NONE) {
		
		m_Transform->X = m_LastSafePosition.X;

		m_RigidBody->InverseForceX(m_Bounciness);
	}

	//  move on Y axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	CollisionType collision_y = CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox());

	if (collision_y != CollisionType::NONE) {

		if (collision_y == CollisionType::DOWN) {
			m_RigidBody->SetSurfaceFriction(10.0f);
			m_IsGrounded = true;
		}

		m_Transform->Y = m_LastSafePosition.Y;

		m_RigidBody->InverseForceY(m_Bounciness);
		
	}
	else {
		m_RigidBody->UnSetSurfaceFriction();
		m_IsGrounded = false;
	}


	if (!m_IsGrounded) {
		m_FallingTime += dt;
	}
	else {
		if (m_FallingTime > 100000.0f) {
			m_TimeToWait = 100.0f;
		}
		m_FallingTime = 0;
	}


	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update();
}

void Acorn::Clean()
{
	TextureManager::GetInstance()->Clean();
}
