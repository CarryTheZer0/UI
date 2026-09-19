/*
 * Face.cpp
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#include <algorithm>
#include <ranges>

#include "Face.h"

Face::Face(glm::vec4 pixels, glm::vec4 percentage) :
	m_pixels(pixels),
	m_percentage(percentage),
	m_isActive(true),
	m_isFocused(false),
	m_focusedChild(0)
{}

Face::Face(float width, float height, float x_offset, float y_offset) :
	m_dimensions(x_offset, y_offset, width, height),
	m_parentDimensions(),
	m_pixels(x_offset, y_offset, width, height),
	m_percentage(),
	m_isActive(true),
	m_isFocused(false),
	m_focusedChild(0)
{}

Face::~Face()
{
	m_children.clear();
}

void Face::draw(IPainter* pPainter)
{
	for (auto face = m_children.begin(); face != m_children.end(); ++face)
	{
		if ((*face)->isActive()) (*face)->draw(pPainter);
	}
}

bool Face::onSelect(bool down, int modifiers)
{
	bool wasSelected = false;
	if (!m_isActive) return wasSelected;

	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasSelected = (*face)->onSelect(down, modifiers);
	}

	return wasSelected;
}

bool Face::onTextInput(char character)
{
	bool wasRead = false;
	if (!m_isActive) return wasRead;

	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasRead = (*face)->onTextInput(character);
	}
	return wasRead;
}

bool Face::onCursorMoved(glm::vec2 position)
{
	bool wasFocused = false;
	if (!m_isActive) return wasFocused;

	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasFocused = (*face)->onCursorMoved(position) || wasFocused;
	}

	if (isInBounds(position) && !wasFocused)
	{
		m_isFocused = true;
		wasFocused = true; // todo call protected onFocused; onCursorMoved becomes private
	}
	else
	{
		m_isFocused = false;
	}
	
	return wasFocused;
}

bool Face::onCursorDragged(glm::vec2 offset)
{
	bool wasDragged = false;
	if (!m_isActive) return wasDragged;

	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasDragged = (*face)->onCursorDragged(offset);
	}

	return wasDragged;
}

bool Face::onScroll(glm::vec2 offset)
{
	bool wasScrolled = false;
	if (!m_isActive) return wasScrolled;

	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		wasScrolled = (*face)->onScroll(offset);
	}

	return wasScrolled;
}

bool Face::cycleFocus()
{
	bool wasShifted = false;
	if (!m_isActive) return wasShifted;

	int firstActiveChild = 0;
	while (firstActiveChild < m_children.size() && !m_children[firstActiveChild]->isActive())
		firstActiveChild++;

	if (isFocused())
	{
		m_isFocused = false;
		if (firstActiveChild < m_children.size())
		{
			m_children[firstActiveChild]->focus();
			wasShifted = true;  // todo call protected onFocused for derived classes; cycleFocus becomes private
		}
	}
	else
	{
		if (m_children.size())
		{
			wasShifted = m_children[m_focusedChild]->cycleFocus();
		}
	}

	if (!wasShifted)
	{
		m_isFocused = false;
		if (m_children.size() > 1)
		{
			for (auto& child : m_children)
				child->unfocus();

			m_focusedChild++;
			while (m_focusedChild < m_children.size() && !m_children[m_focusedChild]->isActive())
				m_focusedChild++;

			if (m_focusedChild < m_children.size()) {
				m_children[m_focusedChild]->focus();
				wasShifted = true;
			}
			else
			{
				m_focusedChild = 0;
			}
		}
		else if (m_children.size() == 1)
		{
			m_isFocused = true;
		}
	}

	return wasShifted;
}

bool Face::shiftFocusLevel(bool down)
{
	return false;
}

bool Face::shiftFocus(glm::vec2 direction)
{
	return false;
}

void Face::setRect()
{
	m_dimensions = m_parentDimensions;

	m_dimensions.x += (m_percentage.x / 100.0f) * m_dimensions.z;
	m_dimensions.y += (m_percentage.y / 100.0f) * m_dimensions.w;
	m_dimensions.z *= m_percentage.z / 100.0f;
	m_dimensions.w *= m_percentage.w / 100.0f;
	
	m_dimensions.x += m_pixels.x;
	m_dimensions.y += m_pixels.y;
	m_dimensions.z += m_pixels.z;
	m_dimensions.w += m_pixels.w;

	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		(*face)->m_parentDimensions = m_dimensions;
		(*face)->setRect();
	}
}

void Face::move(glm::vec2 transform)
{
	// do move
	m_dimensions.x += transform.x;
	m_dimensions.y += transform.y;
	for (auto face = m_children.rbegin(); face != m_children.rend(); ++face)
	{
		(*face)->move(transform);
	}
}

bool Face::isInBounds(glm::vec2 position)
{
	if (position.x > m_dimensions.x && position.y > m_dimensions.y &&
		position.x < m_dimensions.x + m_dimensions.z && position.y < m_dimensions.y + m_dimensions.w)
		return true;
	else
		return false;
}
