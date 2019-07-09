#pragma once
#include "perhapsPch.h"

class Time
{
	static float m_timeDelta;
	static std::chrono::high_resolution_clock::time_point previous;
	static std::chrono::high_resolution_clock::time_point current;

public:
	static float GetTimeDelta();
	static void SetNow();
	static void SwitchPrevious();
};