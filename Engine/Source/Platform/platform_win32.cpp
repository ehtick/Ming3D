#ifdef _WIN32
#include "platform_win32.h"

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "render_device_factory.h"

#ifdef MING3D_OPENGL
#include <GLFW/glfw3.h>
#include "glfw_window.h"
#include "Input/input_handler_glfw.h"
#else
#include "winapi_window.h"
#endif
#include "Input/input_handler_win32.h"

#include "Debug/debug.h"

#pragma comment (lib, "Ws2_32.lib") // REMOVE ME

#include "net_socket_winsock.h"
#include "GameEngine/game_engine.h"

#include "platform_interface_win32.h"
#include <string>

namespace Ming3D
{
    PlatformWin32::PlatformWin32()
    {
        mPlatformInterface = std::make_unique<PlatformInterfaceWin32>();
    }

    PlatformWin32::~PlatformWin32()
    {
        WSACleanup();
    }

    void PlatformWin32::Initialise()
    {
#ifdef MING3D_OPENGL
        if (!glfwInit())
            LOG_ERROR() << "Failed to initialise GLFW";
        else
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RED_BITS, 8);
            glfwWindowHint(GLFW_GREEN_BITS, 8);
            glfwWindowHint(GLFW_BLUE_BITS, 8);
            glfwWindowHint(GLFW_ALPHA_BITS, 8);
            glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
            glfwWindowHint(GLFW_DEPTH_BITS, 24);
            glfwWindowHint(GLFW_STENCIL_BITS, 0);

            LOG_INFO() << "GLFW version: " << glfwGetVersionString();
        }
#endif

        WSADATA wsaData;
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            LOG_ERROR() << "WSAStartup failed";
            return;
        }
    }

    void PlatformWin32::Update()
    {
        MSG msg;
        msg.message = ~WM_QUIT;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
        if (msg.message == WM_QUIT)
        {
            //GGameEngine->Shutdown();
        }
    }

    Rendering::RenderDevice* PlatformWin32::CreateRenderDevice()
    {
        return Rendering::RenderDeviceFactory::CreateRenderDevice();
    }

    Rendering::WindowBase* PlatformWin32::CreateOSWindow()
    {
        Rendering::WindowBase* window;
#ifdef MING3D_OPENGL
        window = new Rendering::GLFWWindow();
#else
        auto wndProcCallback = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT
        {
            InputHandlerWin32* inputHandler = (InputHandlerWin32*)GGameEngine->GetInputHandler();
            return inputHandler->HandleWindowProc(hWnd, message, wParam, lParam);
        };

        window = new Rendering::WinAPIWindow();
        ((Rendering::WinAPIWindow*)window)->mWndProcCallback = wndProcCallback;
#endif
        window->Initialise();
        return window;
    }

    Rendering::RenderWindow* PlatformWin32::CreateRenderWindow(Rendering::WindowBase* inWindow, Rendering::RenderDevice* inDevice)
    {
        return inDevice->CreateRenderWindow(inWindow);
    }

    NetSocket* PlatformWin32::CreateSocket()
    {
        return new NetSocketWinsock();
    }

    InputHandler* PlatformWin32::CreateInputHandler(Rendering::WindowBase* window)
    {
#if MING3D_OPENGL
        return new InputHandlerGLFW(static_cast<Rendering::GLFWWindow*>(window));
#else
        return new InputHandlerWin32();
#endif
    }
    
    std::string PlatformWin32::ReadConsoleLine()
    {
        std::string terminalString;
        std::getline(std::cin, terminalString);
        return std::string(terminalString);
    }
}
#endif
