/*
 * Button.cpp
 *
 *  Created on: 23 Jul 2021
 *      Author: mchlp
 */

// #include <glm/gtx/string_cast.hpp> TODO remove

#include "Button.h"

Button::Button(
		glm::vec4 pixels, 
		glm::vec4 percentage
) :
	Face(pixels, percentage),
	m_color(0.8f, 0.5f, 0.4f),
	m_isHeld(false)
{}

void Button::draw(IPainter* pPainter)
{
	if (isFocused())
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, 10.0f);
    pPainter->drawPanel(m_dimensions, m_color, 10.0f);

	Face::draw(pPainter);
}

void Button::onSelect(bool down, int modifiers)
{
	if (down)
	{
		if (isFocused())
		{
			for (auto& l : m_listeners) l->invoke(true);
			m_isHeld = true;
		}
	}
	else if (m_isHeld)
	{
		for (auto& l : m_listeners) l->invoke(false);
		m_isHeld = false;
	}
}
