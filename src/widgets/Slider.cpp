/*
 *  Slider.cpp
 *
 *  Created on: 
 *      Author: mchlp
 */

#include "Slider.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

Slider::Slider(
		glm::vec4 pixels,
		glm::vec4 percentage,
		float min,
		float max,
		glm::vec3 color,
		float margin
) :
	Face(pixels, percentage),
	m_isHeld(false),
    m_min(min),
    m_max(max),
    m_offset(0.0f),
	m_color(color),
	m_margin(margin)
{
    m_callbackUpdate = [](float f){ return; };
}

void Slider::draw(IPainter* pPainter)
{
	if (isFocused())
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
    pPainter->drawPanel(m_dimensions, m_color, m_margin);
    pPainter->drawPanel(glm::vec4(m_dimensions.x + m_offset, m_dimensions.y, m_dimensions.w, m_dimensions.w), m_color, m_margin);

	Face::draw(pPainter);
}

void Slider::onSelect(bool down, int modifiers)
{	
    if (!down)
    {
        m_isHeld = false;
    }
    else if (isFocused())
    {
        m_isHeld = true;
    }
}

void Slider::onCursorDragged(glm::vec2 offset)
{
    if (m_isHeld)
    {
        setOffset(offset.x);
        updateValue();
    }
}

void Slider::onScroll(glm::vec2 offset)
{
	if (isFocused())
    {
        setOffset(offset.y);
        updateValue();
    }
}

void Slider::updateValue()
{
    m_value = m_min + (m_max - m_min) * (m_offset / (m_dimensions.z - m_dimensions.w));
    m_callbackUpdate(m_value);
}

void Slider::setOffset(float offset)
{
    m_offset += offset;

    // clamp
    if (m_offset + m_dimensions.w > m_dimensions.z) m_offset = m_dimensions.z - m_dimensions.w;
    if (m_offset < 0) m_offset = 0;
}
