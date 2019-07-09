#include "Component.h"
unsigned int Loopable::LoopCount = 0;
std::unordered_map<unsigned int, Loopable*> Loopable::LoopPool;

Loopable::Loopable()
{
	m_ID = Loopable::LoopCount;
	LoopCount++;
	LoopPool.insert(std::make_pair(m_ID, this));
}

Loopable::~Loopable()
{
	LoopPool.erase(m_ID);
}

void Loopable::Start() //virtual function
{
}

void Loopable::Update()//virtual function
{
}

void Loopable::StartLoop()
{
	for (unsigned int i = 0; i < Loopable::LoopPool.size(); i++) //Start() iterations
	{
		(*Loopable::LoopPool.at(i)).Start();
	}
}

void Loopable::UpdateLoop()
{
	for (unsigned int i = 0; i < Loopable::LoopPool.size(); i++) //Update() iterations
	{
		(*Loopable::LoopPool.at(i)).Update();
	}
}
