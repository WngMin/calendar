#pragma once
#include <Windows.h>

class Timer
{
public:
	Timer()
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_secondsPerCount = 1.0 / (double)countsPerSec;
	}
	void Reset()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_preTime = currTime;
		m_cutTime = currTime;
	}
	void Tick()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_cutTime = currTime;
		m_deltaTime = (m_cutTime - m_preTime) * m_secondsPerCount;
		m_preTime = m_cutTime;

		if (m_deltaTime < 0.0)
		{
			m_deltaTime = 0.0;
		}
	}
	double GetDeltaTime() { return m_deltaTime; }
private:
	__int64 m_cutTime;
	__int64 m_preTime;

	double m_secondsPerCount;
	double m_deltaTime;
};