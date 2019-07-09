#pragma once
#include "perhapsPch.h"

//Gain render loop functionality
class Loopable
{
	static unsigned int LoopCount;
	unsigned int m_ID;
	static std::unordered_map<unsigned int, Loopable*> LoopPool;
	public:
	Loopable();
	~Loopable();
	//Called before the first frame.
	virtual void Start();
	//Called once every frame.
	virtual void Update();
	//used for invoking all Start containing Loopables
	static void StartLoop();
	//used for invoking all Update containing Loopables
	static void UpdateLoop();
};