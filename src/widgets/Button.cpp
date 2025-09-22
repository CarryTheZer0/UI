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
	if (true)
	{
		pPainter->drawPanel(m_dimensions, m_color, m_margin);
	}

	Face::draw(pPainter);
}

void Button::onCursorButton(glm::vec2 pos, bool down, unsigned int button)
{
	Face::onCursorButton(pos, down, button);
	if (down)
	{
		if (m_isSelected)
		{
			m_callbackDown();
			m_isHeld = true;
		}
	}
	else if (m_isHeld)
	{
		m_callbackUp();
		m_isHeld = false;
	}
}
