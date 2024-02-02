#pragma once

#include "Vector2D.hpp"
#include <vector>

constexpr auto UNI_MASS = 1.0f;
constexpr auto GRAVITY = 1.0f;
constexpr auto AIR_FRICTION = 0.2f;
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

	// Momentum
	inline void UnSetMomentumY() { m_Velocity.Y = 0; }

	// Force
	inline void ApplyForce(Vector2D force, float deltaTime = 0.1) { m_Forces.push_back(Force(force, deltaTime)); }
	inline void ApplyForceX(float Fx, float deltaTime = 0.1) { m_Forces.push_back(Force(Vector2D(Fx, 0), deltaTime)); }
	inline void ApplyForceY(float Fy, float deltaTime = 0.1) { m_Forces.push_back(Force(Vector2D(0, Fy), deltaTime)); }
	inline void UnSetForce() {m_Forces.clear(); }

	// Friction
	inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
	inline void UnSetFriction() { m_Friction = Vector2D(); }

	// Getters
	inline float GetMass() { return m_Mass; }
	inline Vector2D GetPosition() { return m_Position; }
	inline Vector2D GetVelocity() { return m_Velocity; }
	inline Vector2D GetAcceleration() { return m_Acceleration; }

	// Update methods
	void Update(float dt) {
		//Calculate air friction
		Vector2D air_friction = m_Velocity * AIR_FRICTION;

		int all_forces_x = 0;
		int all_forces_y = 0;

		for (auto& force : m_Forces) {
			// Calculate acceleration
			all_forces_x += force.force.X;
			//m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
			all_forces_y += force.force.Y;
			if (force.force.Y != 0) {
				SDL_Log("Force: %f", force.force.Y);
			}

			force.deltaTime -= dt;

		}
		for (std::vector<Force>::iterator iter = m_Forces.begin(); iter != m_Forces.end(); ++iter)
		{
			if (iter->deltaTime <= 0)
			{
				m_Forces.erase(iter);
				break;
			}
		}

		m_Acceleration.X = (all_forces_x + m_Friction.X) * SURFACE_FRICTION * 4 / m_Mass;

		m_Acceleration.Y = m_Gravity + all_forces_y / m_Mass - air_friction.Y;

		// Calculate velocity
		m_Velocity = m_Velocity + m_Acceleration * dt;
		if (m_Forces.size() > 0) {
		SDL_Log("Velocity: %f", m_Velocity.Y);
		}

		//SDL_Log("Velocity: %f, %f", m_Velocity.X, m_Velocity.Y);

		// Calculate position
		m_Position = m_Velocity * dt;

		//Calculate surface friction
		m_Velocity.X = m_Velocity.X - m_Velocity.X * SURFACE_FRICTION;

		//Calculate friction
		//m_Velocity = m_Velocity - m_Velocity * m_Friction * dt;

		// Calculate gravity
		//m_Velocity.Y = m_Velocity.Y - m_Gravity * dt;

	}

private:
	float m_Mass;
	float m_Gravity;

	std::vector<Force> m_Forces;
	Vector2D m_Friction;

	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_Acceleration;
};