/*
 * helloWorld.cpp
 *
 *  27 July 2023
 *  Mike
 */

#include <iostream>
#include <nlohmann/json.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/gtx/string_cast.hpp>

#include "DebugRenderer.h"
#include "InputHandler.h"
#include "Shader.h"
#include "DebugPainter.h"

#include "Panel.h"
#include "Slider.h"
#include "Button.h"
#include "TextBox.h"
#include "Popup.h"
#include "LineGraph.h"
#include "Draggable.h"

using namespace temp_UI;
using json = nlohmann::json;

class ButtonListener : public IButtonListener
{
public:
    ButtonListener() = default;
    ~ButtonListener() {}

    void invoke(bool down) override
    {
        if (down)
        {
            json test;
            std::string next = "123";
            textBox->append(next);
        }
    }

    TextBox* textBox;
};


/*
 *  General purpose testing script
 */
int main()
{
    glewExperimental=true;
    if (!glfwInit() )
    {
        fprintf( stderr, "Failed to initialise GLFW\n" );
        return -1;
    }

    int width = 1024; int height = 768;

    GLFWwindow* pWindow;
	pWindow = glfwCreateWindow( width, height, "Test 01", NULL, NULL);
    glfwMakeContextCurrent(pWindow);

    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        fprintf( stderr, "Failed to initialize GLEW\n" );
        return -1;
    }

    Shader s = Shader();
    s.loadShaderFromFile("../src/graphics/shaders/LineVertexShader.glsl", "../src/graphics/shaders/LineFragmentShader.glsl");

    Shader s2 = Shader();
    s2.loadShaderFromFile("TextVertexShader.glsl", "TextFragmentShader.glsl");

    DebugRenderer renderer = DebugRenderer(s, s2, width, height);
    
	glfwWindowHint(GLFW_SAMPLES, 4);  // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.3g
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

    bool running = true;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DebugPainter painter = DebugPainter(&renderer);
    Face root = Face(1024.0f, 768.0f);

    // LineGraph graph = LineGraph(root, -0.1f, 1.5f, glm::vec4(10.0f, 10.0f, 500.0f, 500.0f));
    // graph.setData({0.5f,0.3f, 0.4f, 1.5f, -0.1f, 0.8f, 0.4f});
    // root.addChild(graph);

    Panel& panel = root.addChild<Panel>(glm::vec4(), glm::vec4(5.0f, 5.0f, 90.0f, 90.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    Popup& popup = panel.addChild<Popup>(glm::vec4(), glm::vec4(50.0f, 40.0f, 5.0f, 5.0f), glm::vec3(1.0f, 0.0f, 1.0f), 30.0f);

    TextBox& textBox = panel.addChild<TextBox>(glm::vec4(10.0f, 10.0f, 100.0f, 50.0f), glm::vec4(), glm::vec3(1.0f, 1.0f, 0.0f), 10.0f);
    Button& button = popup.addChild<Button>(glm::vec4(), glm::vec4(100.0f, 0.0f, 120.0f, 200.0f));
    ButtonListener* pListener = button.addListener<ButtonListener>();
    pListener->textBox = &textBox;

    TextBox& textBox2 = textBox.addChild<TextBox>(glm::vec4(10.0f, 10.0f, 80.0f, 30.0f), glm::vec4(), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f);

    std::function<void(float)> myfuncSlider = [](float val){std::cout << "slide " << val << std::endl;};
    Slider& slider = panel.addChild<Slider>(glm::vec4(0.0f, 30.0f, 0.0f, 10.0f), glm::vec4(10.0f, 50.0f, 40.0f, 0.0f), 0.0f, 100.0f, glm::vec3(0.0f, 0.0f, 1.0f), 30.0f);
    slider.setCallbackUpdate(myfuncSlider);

    // std::shared_ptr<Slider> slider2 = std::make_shared<Slider>(-1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 50.0f), glm::vec4(10.0f, 50.0f, 40.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // panel->addChild(slider2);
    // slider2->setCallbackUpdate(myfuncSlider);

    // std::shared_ptr<Slider> slider3 = std::make_shared<Slider>(100.0f, 20.0f, glm::vec4(0.0f, 10.0f, 0.0f, 10.0f), glm::vec4(0.0f, 0.0f, 40.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 30.0f);
    // slider2->addChild(slider3);
    // slider3->setCallbackUpdate(myfuncSlider);

    Draggable& drag = popup.addChild<Draggable>(glm::vec4(0.0f, 0.0f, 50.0f, 50.0f), glm::vec4(90.0f, 90.0f, 0.0f, 0.0f), true);

    // {std::shared_ptr<Button> button2 = std::make_shared<Button>(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec4(40.0f, 10.0f, 20.0f, 20.0f), glm::vec3(1.0f, 1.0f, 0.0f), 30.0f);
    // drag->addChild(button2);
    // drag->removeChild(button2);}
    temp_UI::InputHandler input = temp_UI::InputHandler(&root);

    glfwSetWindowUserPointer( pWindow, &input );

    glfwSetCursorPosCallback( pWindow, []( GLFWwindow* window, double x, double y)
    {
        temp_UI::InputHandler* input = static_cast<temp_UI::InputHandler*>( glfwGetWindowUserPointer( window ) );

        // x = -1.0f + 2 * x / 1024.0f;
        // y = -1.0f + 2 * (768.0f - y) / 768.0f;
        y = (768.0f - y);

        glm::mat4 view = glm::lookAt(
            glm::vec3(0,0,1),  // location
            glm::vec3(0,0,0),  // target
            glm::vec3(0,1,0)   // orientation (up direction)
        );

        // ortho camera :
        glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f); // In world coordinates

        glm::vec4 pos = glm::inverse(projection) * glm::inverse(view) * glm::vec4(x, y, 0.0f, 1.0f);

        input->mouseMoveCallback(x, y);
    });

    glfwSetMouseButtonCallback( pWindow, []( GLFWwindow* window, int button, int action, int mods)
    {
        temp_UI::InputHandler* input = static_cast<temp_UI::InputHandler*>( glfwGetWindowUserPointer( window ) );
        input->mouseCallback(button, action, mods);
    });

    glfwSetScrollCallback( pWindow, [](GLFWwindow* window, double x, double y)
    {
        temp_UI::InputHandler* input = static_cast<temp_UI::InputHandler*>( glfwGetWindowUserPointer( window ) );
        input->scrollCallback(x, y);
    });

    glfwSetKeyCallback( pWindow, []( GLFWwindow* window, int key, int scancode, int action, int mods )
    {
        temp_UI::InputHandler* input = static_cast<temp_UI::InputHandler*>( glfwGetWindowUserPointer( window ) );
        input->keyCallback(key, action, mods);
    });

    glfwSetCharCallback( pWindow, []( GLFWwindow* window, unsigned int codepoint) {
        temp_UI::InputHandler* input = static_cast<temp_UI::InputHandler*>( glfwGetWindowUserPointer( window ) );
        input->charCallback(codepoint);
    });

    while(running) {
        glfwPollEvents();

		// render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        root.draw(&painter);
        renderer.drawLines();
        renderer.drawQuads();

        if (glfwWindowShouldClose(pWindow)) {
            running = false;
        }
        glfwSwapBuffers(pWindow);
    }

	glfwTerminate();
}
