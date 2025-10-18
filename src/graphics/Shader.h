/*
 * Shader.h
 *
 *  28 July 2023
 *  Mike
 */

#ifndef UI_SHADER_H_
#define UI_SHADER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader() {}
    ~Shader() = default;
    void use();
    void loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile);

    void setMvpMatrix(const char *name, const glm::mat4 &matrix, bool useShader=false);

    unsigned int getID() { return m_ID; }
private:
    unsigned int m_ID;
    void checkCompileErrors(unsigned int object, std::string type);
    void compile(const char* vertexSource, const char* fragmentSource);
};

#endif /* UI_SHADER_H_ */