#include "stdafx.h"
#include "entity_asteroid.h"
#include "game.h"
#include "globals.h"
#include "component.h"

void Asteroid::update() {
	std::vector<Component*> m_Components = this->getComponents();	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Update();
	}

}

void Asteroid::onCollision(vec2 pos, Entity *otherEntity) {

	ComponentMovable *compMove = FindComponent<ComponentMovable>();
	if (compMove)
	{		
		compMove->setVel(vmake(compMove->getVel().x * -1.0, compMove->getVel().y * -1.0));
		
	}
}


template<class T>
T* Asteroid::FindComponent()
{	
	std::vector<Component*> m_Components = this->getComponents();
	for (auto compIt = m_Components.begin();
		compIt != m_Components.end();
		++compIt)
	{
		T* comp = dynamic_cast<T*>(*compIt);
		if (comp)
			return comp;
	}
	return NULL;
}

bool Asteroid::isCollisionable() {
	ComponentCollisionable *comp = FindComponent<ComponentCollisionable>();
	if (comp)
		return true;
	else
		return false;
}
