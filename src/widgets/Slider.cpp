
#include "Slider.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

Slider::Slider(glm::vec3 color, float margin) :
	Face(),
	m_held(false),
	m_color(color),
	m_margin(margin),
    m_offset(0.0f),
    m_min(0.0f),
    m_max(100.0f)
{}

void Slider::draw(IPainter* pPainter)
{
	if (true)
	{
        pPainter->drawPanel(m_dimensions, m_color, m_margin);
        pPainter->drawPanel(glm::vec4(m_dimensions.x + m_offset, m_dimensions.y, m_dimensions.w, m_dimensions.w), m_color, m_margin);
	}

	Face::draw(pPainter);
}

void Slider::onCursorButton(glm::vec2 pos, bool down, unsigned int button)
{
    Face::onCursorButton(pos, down, button);
	if (!down)
        m_held = false;
    else if (m_isSelected)
        m_held = true;
}

void Slider::onCursorDragged(glm::vec2 offset)
{
    Face::onCursorDragged(offset);
	if (m_held)
    {
        setOffset(offset.x);
        updateValue();
    }
}

bool Slider::onScroll(glm::vec2 offset)
{
    if (Face::onScroll(offset))
        return true;

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
}

void Slider::setOffset(float offset)
{
    m_offset += offset;

    // clamp
    if (m_offset + m_dimensions.w > m_dimensions.z) m_offset = m_dimensions.z - m_dimensions.w;
    if (m_offset < 0) m_offset = 0;
}