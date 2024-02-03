#pragma once

#include "Vector2D.hpp"
#include <vector>

constexpr auto UNI_MASS = 5.0f;
constexpr auto GRAVITY = 1.0f;
constexpr auto AIR_FRICTION = 0.05f;
constexpr auto SURFACE_FRICTION = 0.1f;

struct Force {
	Vector2D force;
	float deltaTime;

	Force(Vector2D f, float dt = 0.1) : force(f), deltaTime(dt) {}
};

class RigidBody {
public:
	RigidBody() {
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}

	// Setter Gravity & Mass
	inline void SetMass(float mass) { m_Mass = mass; }
	inline void SetGravity(float gravity) { m_Gravity = gravity; }
	inline void SetSurfaceFriction(float surface_friction) { m_SurfaceFriction = surface_friction; }
	inline void UnSetSurfaceFriction() { m_SurfaceFriction = 0; }

	// Momentum
	inline void UnSetMomentumY() { m_Velocity.Y = 0; }

	// Force
	inline void ApplyForce(Vector2D force, float deltaTime = 0.1) { m_Forces.push_back(Force(force, deltaTime)); }
	inline void ApplyForceX(float Fx, float deltaTime = 0.1) { m_Forces.push_back(Force(Vector2D(Fx, 0), deltaTime)); }
	inline void ApplyForceY(float Fy, float deltaTime = 0.1) { m_Forces.push_back(Force(Vector2D(0, Fy), deltaTime)); }
	inline void UnSetForce() { m_Forces.clear(); }

	// Friction
	inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
	inline void UnSetFriction() { m_Friction = Vector2D(); }

	// Getters
	inline float GetMass() { return m_Mass; }
	inline Vector2D GetPosition() { return m_Position; }
	inline Vector2D GetVelocity() { return m_Velocity; }
	inline Vector2D GetAcceleration() { return m_Acceleration; }

	void InverseForceX(float bounciness = 0.0f) {
		m_Velocity.X = -m_Velocity.X * bounciness;
	}

	void InverseForceY(float bounciness = 0.0f) {
		m_Velocity.Y = -m_Velocity.Y * bounciness;
	}

	// Update methods
	void Update(float dt) {
		//Calculate air friction
		Vector2D air_friction = m_Velocity * AIR_FRICTION;

		// apply forces to velocity
		this->ApplyForcesToVelocity(dt);

		// apply gravity
		m_Velocity.Y = m_Velocity.Y + m_Gravity / m_Mass * dt;

		// apply air friction
		m_Velocity = m_Velocity - (air_friction  / m_Mass) * dt;

		// apply surface friction
		this->ApplySurfaceFriction(dt);

		//m_Acceleration.X = (all_forces_x + m_Friction.X) /** SURFACE_FRICTION * 4*/ / m_Mass - air_friction.X / 2;

		//m_Acceleration.Y = m_Gravity + all_forces_y / m_Mass - air_friction.Y;

		//SDL_Log("Velocity: %f, %f", m_Velocity.X, m_Velocity.Y);

		// Calculate position
		m_Position = m_Velocity * dt;
	}


private:

	void ApplyForcesToVelocity(float dt) {
		// calculate velocity using all forces
		for (auto& force : m_Forces) {

			float deltaTimeUsed = force.deltaTime;
			if (force.deltaTime > dt) {
				deltaTimeUsed = dt;
			}

			m_Velocity = m_Velocity + (force.force / m_Mass) * deltaTimeUsed;

			force.deltaTime -= dt;

		}

		// remove forces that have been used (their deltaTime is now < 0)
		this->DeleteUsedForces();
	}

	void DeleteUsedForces() {
		// remove forces that have been used (their deltaTime is now < 0)
		for (std::vector<Force>::iterator iter = m_Forces.begin(); iter != m_Forces.end(); ++iter)
		{
			if (iter->deltaTime <= 0)
			{
				m_Forces.erase(iter);
				break;
			}
		}
	}

	void ApplySurfaceFriction(float dt) {

		Vector2D surface_friction = Vector2D(m_SurfaceFriction * GRAVITY, 0);

		// apply surface friction
		if (m_Velocity.X > 0) {
			m_Velocity.X = m_Velocity.X - surface_friction.X * (1 / m_Mass) * dt;
			if (m_Velocity.X < 0) {
				m_Velocity.X = 0;
			}
		}
		else {
			m_Velocity.X = m_Velocity.X + surface_friction.X * (1 / m_Mass) * dt;
			if (m_Velocity.X > 0) {
				m_Velocity.X = 0;
			}
		}
	}

private:
	float m_Mass;
	float m_Gravity;

	float m_SurfaceFriction;

	std::vector<Force> m_Forces;
	Vector2D m_Friction;

	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_Acceleration;
};