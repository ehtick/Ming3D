#include "input_handler_glfw.h"
#include "GameEngine/game_engine.h"
#include "input_manager.h"
#include "glfw_window.h"
#include <GLFW/glfw3.h>

namespace Ming3D
{
    InputHandlerGLFW::InputHandlerGLFW(Rendering::GLFWWindow* window)
    {
        mWindow = window;
    }

    InputHandlerGLFW::~InputHandlerGLFW()
    {

    }

    void InputHandlerGLFW::Initialise()
    {
        mGLFWWindow = mWindow->GetGLFWWindow();
        glfwSetWindowUserPointer(mGLFWWindow, this);
        glfwSetKeyCallback(mGLFWWindow, KeyCallback);
        glfwSetMouseButtonCallback(mGLFWWindow, MouseButtonCallback);
        glfwSetCursorPosCallback(mGLFWWindow, CursorPosCallback);
        glfwSetWindowCloseCallback(mGLFWWindow, WindowCloseCallback);
    }

    void InputHandlerGLFW::Update()
    {
        glfwPollEvents();
        HandleGamepadInput();
    }

    void InputHandlerGLFW::KeyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
    {
        if (action == GLFW_REPEAT)
            return;

        auto* handler = static_cast<InputHandlerGLFW*>(glfwGetWindowUserPointer(window));
        handler->HandleKeyEvent(key, action);
    }

    void InputHandlerGLFW::MouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/)
    {
        auto* handler = static_cast<InputHandlerGLFW*>(glfwGetWindowUserPointer(window));
        handler->HandleMouseButtonEvent(button, action);
    }

    void InputHandlerGLFW::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
    {
        auto* handler = static_cast<InputHandlerGLFW*>(glfwGetWindowUserPointer(window));
        handler->HandleCursorPos(xpos, ypos);
    }

    void InputHandlerGLFW::WindowCloseCallback(GLFWwindow* window)
    {
        auto* handler = static_cast<InputHandlerGLFW*>(glfwGetWindowUserPointer(window));
        handler->mWindow->Close();
    }

    void InputHandlerGLFW::HandleKeyEvent(int key, int action)
    {
        InputEvent inputEvent{};
        inputEvent.mType = (action == GLFW_PRESS) ? InputEventType::KeyDown : InputEventType::KeyUp;
        inputEvent.mKey.mKeyCode = GetKeyCode(key);
        if (inputEvent.mKey.mKeyCode != KeyCode::None)
            AddInputEvent(inputEvent);
    }

    void InputHandlerGLFW::HandleMouseButtonEvent(int button, int action)
    {
        InputEvent inputEvent{};
        inputEvent.mType = (action == GLFW_PRESS) ? InputEventType::MouseButtonDown : InputEventType::MouseButtonUp;
        inputEvent.mMouseButton.mButton = GetMouseButton(button);
        AddInputEvent(inputEvent);
    }

    void InputHandlerGLFW::HandleCursorPos(double xpos, double ypos)
    {
        glm::ivec2 newMousePos = glm::ivec2(static_cast<int>(xpos), static_cast<int>(ypos));
        if (newMousePos != mMousePosition)
        {
            mMousePosition = newMousePos;
            InputEvent inputEvent{};
            inputEvent.mType = InputEventType::MouseMove;
            inputEvent.mMousePosition = mMousePosition;
            AddInputEvent(inputEvent);
        }
    }

    void InputHandlerGLFW::HandleGamepadInput()
    {
        GLFWgamepadstate state;
        if (!glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
            return;

        // Buttons
        static unsigned char prevButtons[GLFW_GAMEPAD_BUTTON_LAST + 1] = {};
        for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
        {
            if (state.buttons[i] != prevButtons[i])
            {
                KeyCode kc = GetGamepadKeyCode(i);
                if (kc != KeyCode::None)
                {
                    InputEvent inputEvent{};
                    inputEvent.mType = state.buttons[i] ? InputEventType::KeyDown : InputEventType::KeyUp;
                    inputEvent.mKey.mKeyCode = kc;
                    AddInputEvent(inputEvent);
                }
                prevButtons[i] = state.buttons[i];
            }
        }

        // Axes
        auto normalizeAxis = [](float value) -> float { return value; };

        float lx = normalizeAxis(state.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
        float ly = normalizeAxis(state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
        if (lx != mLeftControllerAxis.x || ly != mLeftControllerAxis.y)
        {
            mLeftControllerAxis = glm::vec2(lx, ly);
            InputEvent inputEvent{};
            inputEvent.mType = InputEventType::Axis2D;
            inputEvent.mAxis.mAxis = EAxis2D::ControllerAxisLeft;
            inputEvent.mAxis.mValue = mLeftControllerAxis;
            AddInputEvent(inputEvent);
        }

        float rx = normalizeAxis(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
        float ry = normalizeAxis(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
        if (rx != mRightControllerAxis.x || ry != mRightControllerAxis.y)
        {
            mRightControllerAxis = glm::vec2(rx, ry);
            InputEvent inputEvent{};
            inputEvent.mType = InputEventType::Axis2D;
            inputEvent.mAxis.mAxis = EAxis2D::ControllerAxisRight;
            inputEvent.mAxis.mValue = mRightControllerAxis;
            AddInputEvent(inputEvent);
        }
    }

    KeyCode InputHandlerGLFW::GetKeyCode(int glfwKey)
    {
        switch (glfwKey)
        {
        case GLFW_KEY_LEFT_CONTROL: return KeyCode::Key_Ctrl;
        case GLFW_KEY_RIGHT_CONTROL: return KeyCode::Key_Ctrl;
        case GLFW_KEY_LEFT_SUPER: return KeyCode::Key_Win;
        case GLFW_KEY_LEFT_SHIFT: return KeyCode::Key_Shift;
        case GLFW_KEY_RIGHT_SHIFT: return KeyCode::Key_Shift;
        case GLFW_KEY_ENTER: return KeyCode::Key_Enter;
        case GLFW_KEY_SPACE: return KeyCode::Key_Space;
        case GLFW_KEY_UP: return KeyCode::Key_Up;
        case GLFW_KEY_DOWN: return KeyCode::Key_Down;
        case GLFW_KEY_RIGHT: return KeyCode::Key_Right;
        case GLFW_KEY_LEFT: return KeyCode::Key_Left;
        case GLFW_KEY_0: return KeyCode::Key_0;
        case GLFW_KEY_1: return KeyCode::Key_1;
        case GLFW_KEY_2: return KeyCode::Key_2;
        case GLFW_KEY_3: return KeyCode::Key_3;
        case GLFW_KEY_4: return KeyCode::Key_4;
        case GLFW_KEY_5: return KeyCode::Key_5;
        case GLFW_KEY_6: return KeyCode::Key_6;
        case GLFW_KEY_7: return KeyCode::Key_7;
        case GLFW_KEY_8: return KeyCode::Key_8;
        case GLFW_KEY_9: return KeyCode::Key_9;
        case GLFW_KEY_Q: return KeyCode::Key_Q;
        case GLFW_KEY_W: return KeyCode::Key_W;
        case GLFW_KEY_E: return KeyCode::Key_E;
        case GLFW_KEY_R: return KeyCode::Key_R;
        case GLFW_KEY_T: return KeyCode::Key_T;
        case GLFW_KEY_Y: return KeyCode::Key_Y;
        case GLFW_KEY_U: return KeyCode::Key_U;
        case GLFW_KEY_I: return KeyCode::Key_I;
        case GLFW_KEY_O: return KeyCode::Key_O;
        case GLFW_KEY_P: return KeyCode::Key_P;
        case GLFW_KEY_A: return KeyCode::Key_A;
        case GLFW_KEY_S: return KeyCode::Key_S;
        case GLFW_KEY_D: return KeyCode::Key_D;
        case GLFW_KEY_F: return KeyCode::Key_F;
        case GLFW_KEY_G: return KeyCode::Key_G;
        case GLFW_KEY_H: return KeyCode::Key_H;
        case GLFW_KEY_J: return KeyCode::Key_J;
        case GLFW_KEY_K: return KeyCode::Key_K;
        case GLFW_KEY_L: return KeyCode::Key_L;
        case GLFW_KEY_Z: return KeyCode::Key_Z;
        case GLFW_KEY_X: return KeyCode::Key_X;
        case GLFW_KEY_C: return KeyCode::Key_C;
        case GLFW_KEY_V: return KeyCode::Key_V;
        case GLFW_KEY_B: return KeyCode::Key_B;
        case GLFW_KEY_N: return KeyCode::Key_N;
        case GLFW_KEY_M: return KeyCode::Key_M;
        default:
            return KeyCode::None;
        }
    }

    KeyCode InputHandlerGLFW::GetGamepadKeyCode(int button)
    {
        switch (button)
        {
        case GLFW_GAMEPAD_BUTTON_A: return KeyCode::Pad_A;
        case GLFW_GAMEPAD_BUTTON_B: return KeyCode::Pad_B;
        case GLFW_GAMEPAD_BUTTON_X: return KeyCode::Pad_X;
        case GLFW_GAMEPAD_BUTTON_Y: return KeyCode::Pad_Y;
        default:
            return KeyCode::None;
        }
    }

    int InputHandlerGLFW::GetMouseButton(int buttonId)
    {
        // GLFW: LEFT=0, RIGHT=1, MIDDLE=2
        // Engine expects: LEFT=0, MIDDLE=1, RIGHT=2
        switch (buttonId)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                return 0;
            case GLFW_MOUSE_BUTTON_RIGHT:
                return 2;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                return 1;
            default:
                return buttonId;
        }
    }

    void InputHandlerGLFW::AddInputEvent(InputEvent event)
    {
        event.mMousePosition = mMousePosition;
        GGameEngine->GetInputManager()->AddInputEvent(event);
    }
}
