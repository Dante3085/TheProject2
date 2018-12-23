#pragma once
#include <map>

#include "State.h"
#include "Enums.h"

namespace TheProject
{
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine(std::map<EState, State*> states);
		~FiniteStateMachine();

		void update(float deltaTime);
		void changeState(EState state);

	private:
		std::map<EState, State*> m_states;
		EState m_currentState;
	};
}