#include "Time.h"
std::chrono::high_resolution_clock::time_point Time::previous = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point Time::current;
float Time::m_timeDelta = 0;

float Time::GetTimeDelta()
{
	return m_timeDelta;
}

void Time::SetNow()
{
	current = std::chrono::high_resolution_clock::now();
}

void Time::SwitchPrevious()
{
	std::chrono::duration<float> delta = std::chrono::duration_cast<std::chrono::duration<float>>(current - previous);
	m_timeDelta = delta.count();

	previous = current;
}