/*
 * Button.cpp
 *
 *  Created on: 23 Jul 2021
 *      Author: mchlp
 */

#include <glm/gtx/string_cast.hpp>

#include "Button.h"

Button::Button(
		glm::vec4 pixels, 
		glm::vec4 percentage,
		glm::vec3 color,
		float margin
) :
	Face(pixels, percentage),
	m_color(color),
	m_margin(margin)
{}

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
			for (auto& l : m_listeners) l->invoke(true);
			m_isHeld = true;
			return true;
		}
	}
	else if (m_isHeld)
	{
		for (auto& l : m_listeners) l->invoke(false);
		m_isHeld = false;
		return false;
	}

	return false;
}
