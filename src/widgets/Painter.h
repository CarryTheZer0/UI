/*
 * Painter.h
 *
 *  Created on: 22 Jul 2021
 *      Author: mchlp
 */

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif /* M_PI */

#ifndef UI_PAINTER_H_
#define UI_PAINTER_H_


#include <vector>
#include <glm/glm.hpp>

#include "Triangles.h"
#include "IPainter.h"

class UIRenderer;

class Painter : public IPainter
{
public:
	Painter() = default;
	Painter(UIRenderer* pRenderer, const char* name);
	~Painter() = default;

	void drawPanel(glm::vec4 dimensions, glm::vec3 color, float margin) override;
	void drawMenu() override;
	void drawButton() override;
private:
	UIRenderer* m_pRenderer;
};

#endif /* UI_PAINTER_H */
