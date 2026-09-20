/*
 *  LineGraph.cpp
 *
 *  Created on: 19 May 2026
 *      Author: mchlp
 */


#include "LineGraph.h"


LineGraph::LineGraph(
	glm::vec4 pixels, 
	glm::vec4 percentage,
    float min,    
    float max,
	glm::vec3 color
) :
	Face(pixels, percentage),
	m_color(color),
    m_min(min),
    m_max(max)
{}

void LineGraph::setData(std::vector<float> &data)
{ 
    m_data.resize(data.size());
    std::copy(data.begin(), data.end(), m_data.begin()); 
}

void LineGraph::draw(IPainter* pPainter)
{
    size_t size = m_data.size();

    float yScale = m_dimensions.w / (m_max - m_min);
    float xScale = m_dimensions.z / (size - 1);
    
    glm::vec2 prev =  glm::vec2(m_dimensions.x, m_dimensions.y + m_data[0] * yScale);
    glm::vec2 current;
    
    for (int index = 1; index < size; index++)
    {
        current = glm::vec2(m_dimensions.x + index * xScale, m_dimensions.y + (m_data[index] - m_min) * yScale);
        pPainter->drawLine(prev, current, m_color);
        prev = current;
    }
    if (isFocused())
        pPainter->drawPanel(glm::vec4(m_dimensions.x - 1, m_dimensions.y - 1, m_dimensions.z + 2, m_dimensions.w + 2), m_color, 0.0f);
    pPainter->drawPanel(m_dimensions, m_color, 0.0f);
}
