#ifndef ENTITY_H
#define ENTITY_H

#include "Enums.h"

namespace TheProject
{
	class Entity
	{
	public:
		virtual ~Entity() {}
		virtual void update(float deltaTime) = 0;

		virtual bool checkConditions(EState state) = 0;
		virtual void addCondition(EState state, bool(*condition)()) = 0;
	};
}
#endif