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
	m_dimensions(),
	m_parentDimensions(),
	m_pixels(pixels),
	m_percentage(percentage),
	m_isActive(true),
	m_isFocused(false),
	m_isFrozen(false),
	m_holdFocus(false),
	m_focusedChild(0)
{}

Face::Face(float width, float height, float x_offset, float y_offset) :
	m_dimensions(x_offset, y_offset, width, height),
	m_parentDimensions(),
	m_pixels(x_offset, y_offset, width, height),
	m_percentage(),
	m_isActive(true),
	m_isFocused(false),
	m_isFrozen(false),
	m_holdFocus(false),
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

void Face::select(bool down, int modifiers)
{
	if (!m_isActive) return;

	if (m_isFrozen && down) 
		m_isFrozen = false;
	else if (down)
		m_isFrozen = m_isFocused && m_holdFocus;

	for (int index = 0; index < m_children.size(); index++)
	{
		if (m_children[index]->isFocused())
			m_children[index]->onSelect(down, modifiers);

		if (index == m_focusedChild) 
		{
			m_children[index]->select(down, modifiers);
			m_isFrozen |= m_children[m_focusedChild]->isFrozen();
		}
	}
}

void Face::drag(glm::vec2 offset)
{
	if (!m_isActive) return;

	for (int index = 0; index < m_children.size(); index++)
	{
		if (m_children[index]->isFocused())
			m_children[index]->onCursorDragged(offset);

		if (index == m_focusedChild) 
			m_children[index]->drag(offset);
	}
}

void Face::scroll(glm::vec2 offset)
{
	if (!m_isActive) return;

	for (int index = 0; index < m_children.size(); index++)
	{
		if (m_children[index]->isFocused())
			m_children[index]->onScroll(offset);

		if (index == m_focusedChild) 
			m_children[index]->scroll(offset);
	}
}

void Face::textInput(char character)
{
	if (!m_isActive) return;

	for (int index = 0; index < m_children.size(); index++)
	{
		if (m_children[index]->isFocused())
			m_children[index]->onTextInput(character);

		if (index == m_focusedChild) 
			m_children[index]->textInput(character);
	}
}

bool Face::cursorMoved(glm::vec2 position)
{
	bool wasFocused = false;
	if (!m_isActive || m_isFrozen) return wasFocused;

	for (int index = 0; index < m_children.size(); index++) 
	{
		bool childFocused = m_children[index]->cursorMoved(position); 
		if (childFocused)
		{
			m_focusedChild = index;
			wasFocused = true;
		}
	}

	if (isInBounds(position) && !wasFocused)
	{
		focus();
		wasFocused = true;
	}
	else
	{
		unfocus();
	}
	
	return wasFocused;
}

bool Face::tryToShiftFocus()
{
	if (m_focusedChild >= m_children.size()) return false;
	while (!m_children[m_focusedChild]->isActive())
	{
		if (m_focusedChild++ >= m_children.size()) return false;
	}
		
	m_children[m_focusedChild]->focus();
	unfocus();
	return true;
}

bool Face::cycleFocus()
{
	bool wasShifted = false;
	if (!m_isActive || m_isFrozen) return wasShifted;

	if (isFocused())
	{
		m_focusedChild = 0;
		wasShifted = tryToShiftFocus();
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
		if (m_children.size() > 1)
		{
			for (auto& child : m_children)
				child->unfocus();

			m_focusedChild++;
			wasShifted = tryToShiftFocus();
			if (!wasShifted) m_focusedChild = 0;
		}
		else if (m_children.size() == 1)
		{
			focus();
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
