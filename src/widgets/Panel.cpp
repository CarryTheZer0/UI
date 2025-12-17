/*
 * Panel.cpp
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#include <glm/gtx/string_cast.hpp>

#include <vector>

#include "Panel.h"

Panel::Panel(glm::vec3 color, float margin) :
	Face(),
	m_margin(margin),
	m_color(color)
{}

void Panel::draw(IPainter* pPainter)
{
	if (m_isSelected)
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
	pPainter->drawPanel(m_dimensions, m_color, m_margin);
	Face::draw(pPainter);
}
