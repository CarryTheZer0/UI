/*
 * InputHandler.h
 *
 *  04 Aug 2023
 *  Mike
 */

class Face;

namespace temp_UI {
    class InputHandler {
    public:
        InputHandler() = delete;
        InputHandler(Face* pUiRoot);
        ~InputHandler() = default;

        void keyCallback(int key, int scancode, int action, int mods);
        void mouseCallback(int button, int action, int mods);
        void mouseMoveCallback(double xPos, double yPos);
        void scrollCallback(float x, float y);
    private:
        float m_mouseX;
        float m_mouseY;

        Face* m_pUiRoot;
        bool m_pressed;
    };
}