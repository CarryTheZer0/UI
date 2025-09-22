
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif /* M_PI */

#include <vector>
#include <math.h>

#include "Triangles.h"

int drawCircle(std::vector<Vertex>& vertices, std::vector<Triangle>& triangles, float radius, glm::vec2 centre, glm::vec3 color,
					   int centreIndex, int startIndex, int endIndex, int nextIndex, float startAngle, float endAngle, int n)
{
	float x = sinf(startAngle) * radius;
	float y = cosf(startAngle) * radius;

	triangles.emplace_back(Triangle(centreIndex, startIndex, nextIndex));
	vertices.emplace_back(Vertex(centre.x + x, centre.y + y, color));
	for (uint32_t i = 0; i < n-1; i++) {
		float angle = startAngle + ((endAngle - startAngle) * (i+1) / n);
		x = sinf(angle) * radius;
		y = cosf(angle) * radius;
		vertices.emplace_back(Vertex(centre.x + x, centre.y + y, color));
		triangles.emplace_back(Triangle(centreIndex, nextIndex + i, nextIndex + i + 1));
	}
	triangles.emplace_back(Triangle(centreIndex, endIndex, nextIndex + n - 1));

	return nextIndex + n;
}

int drawRoundedRectangle(std::vector<Vertex>& vertices, std::vector<Triangle>& triangles, 
        float ratio, float margin, glm::vec3 color, int nextIndex) {
    // inner corners: TL, TR, BL, BR
	vertices.emplace_back(Vertex(glm::vec2(-1.0f + margin, ratio - margin), color));  	// 0
	vertices.emplace_back(Vertex(glm::vec2(1.0f - margin, ratio - margin), color));		// 1
	vertices.emplace_back(Vertex(glm::vec2(-1.0f + margin, -ratio + margin), color));	// 2
	vertices.emplace_back(Vertex(glm::vec2(1.0f - margin, -ratio + margin), color));	// 3

	// outer top: L, R
	vertices.emplace_back(Vertex(glm::vec2(-1.0f + margin, ratio), color));				// 4
	vertices.emplace_back(Vertex(glm::vec2(1.0f - margin, ratio), color));				// 5

	// outer left: T, B
	vertices.emplace_back(Vertex(glm::vec2(-1.0f, ratio - margin), color));				// 6
	vertices.emplace_back(Vertex(glm::vec2(-1.0f, -ratio + margin), color));			// 7

	// outer right: T, B
	vertices.emplace_back(Vertex(glm::vec2(1.0f, ratio - margin), color));				// 8
	vertices.emplace_back(Vertex(glm::vec2(1.0f, -ratio + margin), color));				// 9

	// outer bottom: L, R
	vertices.emplace_back(Vertex(glm::vec2(-1.0f + margin, -ratio), color));			// 10
	vertices.emplace_back(Vertex(glm::vec2(1.0f - margin, -ratio), color));				// 11

	nextIndex += 12;

	// centre
	triangles.emplace_back(Triangle(4, 5, 11));
	triangles.emplace_back(Triangle(4, 10, 11));

	// left margins
	triangles.emplace_back(Triangle(6, 0, 2));
	triangles.emplace_back(Triangle(6, 7, 2));

	// right margins
	triangles.emplace_back(Triangle(8, 1, 3));
	triangles.emplace_back(Triangle(8, 9, 3));

	float angleUp = (M_PI * 2.0f);
	float angleRight = (M_PI * 0.5f);
	float angleDown = M_PI;
	float angleLeft = (M_PI * 1.5f);

	int trianglesPerCurve = 10;

	nextIndex = drawCircle(vertices, triangles, margin, glm::vec2(-1.0f + margin, ratio - margin),
		color, 0, 6, 4, nextIndex, angleLeft, angleUp, trianglesPerCurve);
	nextIndex = drawCircle(vertices, triangles, margin, glm::vec2(1.0f - margin, ratio - margin), 
		color, 1, 5, 8, nextIndex, 0.0f, angleRight, trianglesPerCurve);
	nextIndex = drawCircle(vertices, triangles, margin, glm::vec2(1.0f - margin, -ratio + margin),
		color, 3, 9, 11, nextIndex, angleRight, angleDown, trianglesPerCurve);
	nextIndex = drawCircle(vertices, triangles, margin, glm::vec2(-1.0f + margin, -ratio + margin),
		color, 2, 10, 7, nextIndex, angleDown, angleLeft, trianglesPerCurve);

	return nextIndex;
}
