#pragma once

constexpr int TARGET_FPS = 60;
constexpr float TARGET_DELTATIME = 1.5f;

class Timer {
public:
	static Timer* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();
	}
	void Tick();
	inline float GetDeltaTime() const { return m_DeltaTime; }

private:
	Timer() {};
	static Timer* s_Instance;
	float m_DeltaTime = 0;
	float m_LastTime;

};