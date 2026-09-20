/*
 *  Popup.h
 *
 *  Created on: 17 Dec 2025
 *      Author: mchlp
 */

#include "Face.h"

class Popup : public Face
{
public:
    Popup() = delete;
	Popup(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
        glm::vec3 color=glm::vec3(1.0f),
		float margin=50.0f
    );

    void draw(IPainter* pPainter) override;

    void onFocused() override;
    void onUnfocused() override;

    template <class FaceType, class... ValueTypes>
	FaceType& addChild(
		glm::vec4 pixels=glm::vec4(), 
		glm::vec4 percentage=glm::vec4(),
		ValueTypes... args
	) {
        FaceType& face = Face::addChild<FaceType, ValueTypes...>(pixels, percentage, args...);
        face.setActive(false);
        return face;
    }
private:
    glm::vec3 m_color;
    float m_margin;
};