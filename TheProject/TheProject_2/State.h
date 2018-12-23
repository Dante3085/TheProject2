#pragma once
#include <vector>

#include "GameObject.h"

namespace TheProject
{
	class State
	{
	public:
		State(std::vector<GameObject*> gameObjects) : m_gameObjects{ gameObjects } {}
		
		virtual void update(float deltaTime)
		{
			for (GameObject* g : m_gameObjects)
				g->update(deltaTime);
		}

		virtual void onEnter() = 0;
		virtual void onExit() = 0;

	private:
		std::vector<GameObject*> m_gameObjects;
	};
}