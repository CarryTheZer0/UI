/*
 * InputHandler.h
 *
 *  04 Aug 2023
 *  Mike
 */


#include <map>

class Face;

namespace temp_UI {
    class InputHandler {
    public:
        InputHandler() = delete;
        InputHandler(Face* pUiRoot);
        ~InputHandler() = default;

        void keyCallback(int key, int action, int modifiers);
        void mouseCallback(int button, int action, int modifiers);
        void mouseMoveCallback(double xPos, double yPos);
        void scrollCallback(float x, float y);
    private:
        float m_mouseX;
        float m_mouseY;

        Face* m_pUiRoot;
        std::map<int, bool> m_pressed;

        void onInput(int id, int action, int modifiers);
    };
}