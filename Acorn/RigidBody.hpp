#pragma once

#include "Vector2D.hpp"

constexpr auto UNI_MASS = 1.0f;
constexpr auto GRAVITY = 9.8f;
constexpr auto AIR_FRICTION = 0.2f;

class RigidBody {
public:
	RigidBody() {
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}

	// Setter Gravity & Mass
	inline void SetMass(float mass) { m_Mass = mass; }
	inline void SetGravity(float gravity) { m_Gravity = gravity; }

	// Force
	inline void ApplyForce(Vector2D force) { m_Force = force; }
	inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
	inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
	inline void UnSetForce() { m_Force = Vector2D(); }

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

		// Calculate acceleration
		m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass - air_friction.Y;

		// Calculate velocity
		m_Velocity = m_Velocity + m_Acceleration * dt;

		SDL_Log("Velocity: %f, %f", m_Velocity.X, m_Velocity.Y);

		// Calculate position
		m_Position = m_Velocity * dt;

		// Calculate friction
		//m_Velocity = m_Velocity - m_Velocity * m_Friction * dt;

		// Calculate gravity
		//m_Velocity.Y = m_Velocity.Y - m_Gravity * dt;

	}

private:
	float m_Mass;
	float m_Gravity;

	Vector2D m_Force;
	Vector2D m_Friction;

	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_Acceleration;
};