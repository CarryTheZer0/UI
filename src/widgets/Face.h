/*
 * Face.h
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
	Face();
	Face(float width, float height);
	virtual ~Face();

	virtual void draw(IPainter* pPainter);

	virtual bool onSelect(bool down, int modifiers);

	virtual bool onCursorMoved(glm::vec2 position);
	virtual bool onCursorDragged(glm::vec2 offset);
	virtual bool onScroll(glm::vec2 offset);

	virtual bool cycleFocus();
	virtual bool shiftFocusLevel(bool down);
	virtual bool shiftFocus(glm::vec2 direction);

	void addChild(std::weak_ptr<Face> child);
	void removeChild(std::weak_ptr<Face> face);
	
	glm::vec4 getRect();
	void setRect(glm::vec4 pixels, glm::vec4 percentage);
protected:
	Face* m_pParent;
	std::vector<std::weak_ptr<Face>> m_children;
	int m_focus;

	glm::vec4 m_dimensions;

	bool m_isSelected; 

	bool isInBounds(glm::vec2 position);
private:
	void select() { m_isSelected = true; } 
	void deselect() { m_isSelected = false; } 
	void setParent(Face* pParent) { m_pParent = pParent; }
};

#endif /* UI_FACE_H_ */
