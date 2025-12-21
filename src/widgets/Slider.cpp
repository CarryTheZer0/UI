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
		Face& parent,
		float min,
		float max,
		glm::vec4 pixels,
		glm::vec4 percentage,
		glm::vec3 color,
		float margin
) :
	Face(parent, pixels, percentage),
	m_held(false),
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
	if (m_isSelected)
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, m_margin);
    pPainter->drawPanel(m_dimensions, m_color, m_margin);
    pPainter->drawPanel(glm::vec4(m_dimensions.x + m_offset, m_dimensions.y, m_dimensions.w, m_dimensions.w), m_color, m_margin);

	Face::draw(pPainter);
}

bool Slider::onSelect(bool down, int modifiers)
{
    if (Face::onSelect(down, modifiers)) return true;
	
    if (!down)
    {
        m_held = false;
        return false;
    }
    else if (m_isSelected)
    {
        m_held = true;
        return true;
    }

    return false;
}

bool Slider::onCursorDragged(glm::vec2 offset)
{
    if (Face::onCursorDragged(offset)) return true;

    if (m_held)
    {
        setOffset(offset.x);
        updateValue();
        return true;
    }

    return false;
}

bool Slider::onScroll(glm::vec2 offset)
{
    if (Face::onScroll(offset)) return true;

	if (m_isSelected)
    {
        setOffset(offset.y);
        updateValue();
        return true;
    }

    return false;
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