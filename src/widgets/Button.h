/*
 * Button.h
 *
 *  Created on: 23 Jul 2021
 *      Author: mchlp
 */

#ifndef UI_BUTTON_H_
#define UI_BUTTON_H_

#include <functional>

#include "Face.h"


class IButtonListener
{
public:
    virtual ~IButtonListener() = 0;

	virtual void invoke(bool down) = 0;
};

inline IButtonListener::~IButtonListener() {}


class Button : public Face
{
public:
	Button() = delete;
	Button(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4()
	);

	void draw(IPainter* pPainter) override;

	bool onSelect(bool down, int modifiers) override;
	
	template <class ListenerType>
	ListenerType* addListener() { 
		m_listeners.push_back(std::make_unique<ListenerType>()); 
		return dynamic_cast<ListenerType*>(m_listeners.back().get()); 
	}
	
	void removeListener(IButtonListener& listenerA)
	{
		auto it = std::find_if(m_listeners.begin(), m_listeners.end(), [&](std::unique_ptr<IButtonListener>& listenerB){ return &listenerA == listenerB.get(); });
		m_listeners.erase(it);
	}
protected:
	glm::vec3 m_color;
	bool m_isHeld;

	std::vector<std::unique_ptr<IButtonListener>> m_listeners;
};

#endif /* UI_BUTTON_H_ */
