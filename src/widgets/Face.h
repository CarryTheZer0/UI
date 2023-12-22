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
	Face() {};
	Face(float width, float height);
	virtual ~Face();

	virtual void draw(IPainter* pPainter);
	// note 'cursor' is temporary, todo implement focus
	virtual void onCursorMoved(glm::vec2 pos);
	virtual void onCursorButton(glm::vec2 pos, bool down, unsigned int button);
	virtual void onCursorDragged(glm::vec2 offset);
	virtual void onScroll(glm::vec2 offset);

	void addChild(Face* pChild);
	glm::vec4 getRect();
	void setRect(glm::vec4 pixels, glm::vec4 percentage);
protected:
	Face* m_pParent;
	std::vector<Face*> m_children;

	glm::vec4 m_dimensions;

	bool m_isSelected; 

	bool isInBounds(glm::vec2 pos);
private:
	void setParent(Face* pParent);
};

#endif /* UI_FACE_H_ */
