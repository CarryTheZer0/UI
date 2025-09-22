/*
 *  DebugRenderer.h
 *
 *  Created on: 18 Jan 2025
 *      Author: mchlp
 */

#ifndef SRC_GRAPHICS_DEBUGRENDERER_H_
#define SRC_GRAPHICS_DEBUGRENDERER_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>

#include "Shader.h"

class DebugRenderer
{
public:
    // Constructor (inits shaders/shapes)
    DebugRenderer() = default;
	DebugRenderer(Shader &shader, Shader &textShader, float width, float height);
    // Destructor
    ~DebugRenderer();
    
    void drawLine(glm::vec2 a, glm::vec2 b, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    void drawCircle(glm::vec2 centre, float radius);
    void drawLines();
    
    void drawString(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    void drawQuads();
    void draw();
private:
    struct Character {
        unsigned int textureID;  // ID handle of the glyph texture
        glm::ivec2   size;       // Size of glyph
        glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
        unsigned int advance;    // Offset to advance to next glyph
    };

    // window dimensions
    float m_windowWidth, m_windowHeight;
    
    // Lines Render state
    Shader       m_lineShader;
    unsigned int m_linesVAO;
    unsigned int m_linesVBO;
    unsigned int m_linesOffset;
    int m_linesBatchSize;  // max number of lines drawn in one drawLines() call
    
    // Text Render state
    Shader       m_textShader;
    unsigned int m_textVAO;
    unsigned int m_textVBO;
    unsigned int m_textIBO;
    int m_texCount;
    std::map<unsigned int, int> m_texIDs;
    unsigned int m_textOffset;
    int m_textBatchSize;  // max number of quads drawn in one drawQuads() call
    
    std::map<char, Character> m_characters;
    
    // Initialises and configures the renderer's buffer and vertex attributes
    void initDebugRenderer();
    void initTextRenderer();
    // Initialises fonts
    void initFont();
};

#endif /* SRC_GRAPHICS_DEBUGRENDERER_H_ */