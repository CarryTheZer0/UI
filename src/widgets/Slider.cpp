
#include "Slider.h"

#include <glm/gtx/string_cast.hpp>

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
        pPainter->drawPanel(glm::vec4(m_dimensions.x + m_offset, m_dimensions.y, m_dimensions.w, m_dimensions.w), glm::vec3(), m_margin);
	}

	Face::draw(pPainter);
}

void Slider::onCursorButton(glm::vec2 pos, bool down, unsigned int button)
{
	if (!down)
        m_held = false;
    else if (m_isSelected)
        m_held = true;
	Face::onCursorButton(pos, down, button);
}

void Slider::onCursorDragged(glm::vec2 offset)
{
	if (m_held)
    {
        setOffset(offset.x);
        getValue();
    }
    Face::onCursorDragged(offset);
}

void Slider::onScroll(glm::vec2 offset)
{
	if (m_isSelected)
    {
        setOffset(offset.y);
        getValue();
    }
    Face::onCursorDragged(offset);
}

float Slider::getValue()
{
     std::cout << "dragged " << m_min + (m_max - m_min) * (m_offset / (m_dimensions.z - m_dimensions.w)) << std::endl;
    return m_min + (m_max - m_min) * (m_offset / (m_dimensions.z - m_dimensions.w));
}

void Slider::setOffset(float offset)
{
    m_offset += offset;

    // clamp
    if (m_offset + m_dimensions.w > m_dimensions.z) m_offset = m_dimensions.z - m_dimensions.w;
    if (m_offset < 0) m_offset = 0;
}