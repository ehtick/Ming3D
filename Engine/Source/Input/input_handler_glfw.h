#ifndef MING3D_INPUTHANDLER_GLFW_H
#define MING3D_INPUTHANDLER_GLFW_H

#include "input_handler.h"
#include "input_event.h"
#include "glm/vec2.hpp"

struct GLFWwindow;

namespace Ming3D
{
    namespace Rendering
    {
        class GLFWWindow;
    }

    class InputHandlerGLFW : public InputHandler
    {
    public:
        InputHandlerGLFW(Rendering::GLFWWindow* window);
        virtual ~InputHandlerGLFW();
        virtual void Initialise() override;
        virtual void Update() override;

    private:
        Rendering::GLFWWindow* mWindow;
        GLFWwindow* mGLFWWindow = nullptr;
        glm::vec2 mLeftControllerAxis;
        glm::vec2 mRightControllerAxis;
        glm::ivec2 mMousePosition;

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        static void WindowCloseCallback(GLFWwindow* window);

        void HandleKeyEvent(int key, int action);
        void HandleMouseButtonEvent(int button, int action);
        void HandleCursorPos(double xpos, double ypos);
        void HandleGamepadInput();

        KeyCode GetKeyCode(int glfwKey);
        KeyCode GetGamepadKeyCode(int button);
        int GetMouseButton(int buttonId);
        void AddInputEvent(InputEvent event);
    };
}

#endif
