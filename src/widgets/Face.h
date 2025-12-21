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

#include "IPainter.h"

class Face
{
public:
	Face() = delete;
	Face(
		Face& pParent, 
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4()
	);
	
	Face(float width, float height, float x_offset=0.0f, float y_offset=0.0f);
	
	virtual ~Face();

	virtual void draw(IPainter* pPainter);

	virtual bool onSelect(bool down, int modifiers);

	virtual bool onCursorMoved(glm::vec2 position);
	virtual bool onCursorDragged(glm::vec2 offset);
	virtual bool onScroll(glm::vec2 offset);

	virtual bool cycleFocus();
	virtual bool shiftFocusLevel(bool down);
	virtual bool shiftFocus(glm::vec2 direction);

	void addChild(Face& child);
	void removeChild(Face& face);
	
	glm::vec4 getRect();
	virtual void setRect(glm::vec4 pixels=glm::vec4(), glm::vec4 percentage=glm::vec4());

	bool isSelected() { return m_isSelected; }
protected:
	Face& m_parent;
	std::vector<Face*> m_children;
	int m_focus;

	glm::vec4 m_dimensions;

	bool m_isSelected; 

	bool isInBounds(glm::vec2 position);
private:
	void select() { m_isSelected = true; } 
	void deselect() { m_isSelected = false; }
};

#endif /* UI_FACE_H_ */
