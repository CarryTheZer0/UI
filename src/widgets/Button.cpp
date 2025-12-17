/*
 * Button.cpp
 *
 *  Created on: 23 Jul 2021
 *      Author: mchlp
 */

#include <glm/gtx/string_cast.hpp>

#include "Button.h"

Button::Button(glm::vec3 color, float margin) :
	Face(),
	m_color(color),
	m_margin(margin),
	m_callbackDown(nullptr),
	m_callbackUp(nullptr)
{
	m_callbackDown = []{return;};
	m_callbackUp = []{return;};
}

void Button::draw(IPainter* pPainter)
{
	if (m_isSelected)
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
    pPainter->drawPanel(m_dimensions, m_color, m_margin);

	Face::draw(pPainter);
}

bool Button::onSelect(bool down, int modifiers)
{
	if (Face::onSelect(down, modifiers)) return true;

	if (down)
	{
		if (m_isSelected)
		{
			m_callbackDown();
			m_isHeld = true;
			return true;
		}
	}
	else if (m_isHeld)
	{
		m_callbackUp();
		m_isHeld = false;
		return false;
	}

	return false;
}
