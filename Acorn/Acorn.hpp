#pragma once

#include <SDL.h>
#include "Character.hpp"
#include "Animation.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Vector2D.hpp"

const float JUMP_TIME = 0.5f;
const float JUMP_FORCE = 5.0f;

class Acorn : public Character{
public:
	Acorn(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	/*int m_Row, m_Frame, m_FrameCount;
	int m_AnimationSpeed;*/

	bool m_IsJumping;
	bool m_IsGrounded;

	float m_JumpTime;
	float m_JumpForce;

	Collider* m_Collider;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;
};