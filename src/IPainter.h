/*
 * IPainter.h
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#ifndef UI_IPAINTER_H_
#define UI_IPAINTER_H_

#include <string>
#include <glm/glm.hpp>

class IPainter
{
public:
    virtual ~IPainter() = 0;

	virtual void drawPanel(glm::vec4 dimensions, glm::vec3 color, float margin) = 0;
	virtual void drawMenu() = 0;
	virtual void drawButton() = 0;
	virtual void drawText(std::string text, glm::vec2 posistion, float scale, glm::vec3 color) = 0;
};

inline IPainter::~IPainter() {}

#endif /* UI_IPAINTER_H_ */