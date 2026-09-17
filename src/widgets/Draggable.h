/*
 *  Draggable.h
 *
 *  Created on: 13 Sep 2026
 *      Author: mchlp
 */

#ifndef UI_DRAGGABLE_H_
#define UI_DRAGGABLE_H_

#include "Face.h"

class Draggable : public Face
{
public:
    Draggable() = delete;
	Draggable(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
        bool clampToParent=true
	);

    bool onSelect(bool down, int modifiers) override;
    bool onCursorDragged(glm::vec2 offset) override;

    void draw(IPainter* pPainter) override;

private:
    bool m_isHeld;
    bool m_clampToParent;
};

#endif /* UI_DRAGGABLE_H_ */
