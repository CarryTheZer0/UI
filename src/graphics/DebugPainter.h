/*
 *  DebugPainter.h
 *
 *  Created on: 18 Jan 2025
 *      Author: mchlp
 */

#ifndef UI_DEBUGPAINTER_H_
#define UI_DEBUGPAINTER_H_

#include <glm/glm.hpp>

#include "IPainter.h"


namespace temp_UI {

class DebugRenderer;

class DebugPainter : public IPainter
{
public:
    DebugPainter() = default;
    DebugPainter(DebugRenderer* pRenderer);
    ~DebugPainter() = default;

	void drawPanel(glm::vec4 dimensions, glm::vec3 color, float margin) override;
    void drawLine(glm::vec2 a, glm::vec2 b, glm::vec3 color) override;
    void drawText(std::string text, glm::vec2 posistion, float scale, glm::vec3 color) override;
private:
    DebugRenderer* m_pRenderer;
};

}

#endif /* UI_DEBUGPAINTER_H_ */