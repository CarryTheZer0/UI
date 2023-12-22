/*
 * Panel.cpp
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#include <iostream>
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
	pPainter->drawPanel(m_dimensions, m_color, m_margin);
	Face::draw(pPainter);
}
