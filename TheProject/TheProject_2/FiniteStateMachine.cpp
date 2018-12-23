#include "FiniteStateMachine.h"


TheProject::FiniteStateMachine::FiniteStateMachine(std::map<EState, State*> states)
	: m_states{ states }, m_currentState{ NONE }
{
}

void TheProject::FiniteStateMachine::update(float deltaTime)
{
	if (m_currentState == NONE)
		return;

	m_states[m_currentState]->update(deltaTime);
}

void TheProject::FiniteStateMachine::changeState(EState state)
{
	// Check if state is known to FSM
	if (m_states.count(state) == 0)
		return;

	m_states[m_currentState]->onExit();
	m_states[state]->onEnter();
	m_currentState = state;
}
