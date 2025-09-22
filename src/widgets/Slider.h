
#include <functional>
#include <glm/glm.hpp>

#include "Face.h"

class Slider : public Face
{
public:
	Slider() = delete;
	Slider(glm::vec3 color, float margin=50.0f);
	~Slider() = default;

	void draw(IPainter* pPainter) override;

	void onCursorButton(glm::vec2 pos, bool down, unsigned int button) override;
	void onCursorDragged(glm::vec2 offset) override;
    bool onScroll(glm::vec2 offset) override;

    void updateValue();
protected:
	glm::vec3 m_color;
	float m_margin;
    bool m_held;
    float m_offset, m_min, m_max;

	float m_value;
private:
    void setOffset(float offset);
};