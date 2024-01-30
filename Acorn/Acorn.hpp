#pragma once

#include <SDL.h>
#include "Character.hpp"
#include "Animation.hpp"
#include "RigidBody.hpp"

class Acorn : public Character{
public:
	Acorn(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	/*int m_Row, m_Frame, m_FrameCount;
	int m_AnimationSpeed;*/

	Animation* m_Animation;
	RigidBody* m_RigidBody;
};