/*
 *  Face.h
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#ifndef UI_FACE_H_
#define UI_FACE_H_

#include <glm/glm.hpp>

#include <vector>
#include <memory>

#include "IPainter.h"

class Face
{
public:
	Face() = delete;
	Face(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4()
	);

	Face(float width, float height, float x_offset=0.0f, float y_offset=0.0f);

	virtual ~Face();

	virtual void draw(IPainter* pPainter);

	/// @return true is the widget was selected
	virtual bool onSelect(bool down, int modifiers);

	virtual bool onCursorMoved(glm::vec2 position);
	virtual bool onCursorDragged(glm::vec2 offset);
	virtual bool onScroll(glm::vec2 offset);

	virtual bool cycleFocus();
	virtual bool shiftFocusLevel(bool down);
	virtual bool shiftFocus(glm::vec2 direction);

	void addChild(std::shared_ptr<Face> child);
	void removeChild(std::shared_ptr<Face> face);
	
	glm::vec4 getRect();
	glm::vec2 getCentre();
	void move(glm::vec2 transform);

	bool isSelected() { return m_isSelected; }
protected:
	glm::vec4 m_parentDimensions;
	glm::vec4 m_pixels;
	glm::vec4 m_percentage;
	glm::vec4 m_dimensions;

	std::vector<std::shared_ptr<Face>> m_children;
	int m_focus;

	bool m_isSelected; 

	void setRect(); 

	bool isInBounds(glm::vec2 position);

	void select() { m_isSelected = true; } 
	void deselect() { m_isSelected = false; }
};

#endif /* UI_FACE_H_ */
