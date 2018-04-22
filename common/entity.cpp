#include "stdafx.h"
#include "entity.h"
#include "component.h"

void Entity::update() {
	//OVERRIDE ON EACH ENTITY

	//for (auto compIt = m_Components.begin(); compIt != m_Components.end();	++compIt) {
	//	(*compIt)->Update();
	//}

}

void Entity::receiveMessage(Message *msg)
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); 	++compIt)
		(*compIt)->receiveMessage(msg);

}template<class T>
T* Entity::FindComponent()
{
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
