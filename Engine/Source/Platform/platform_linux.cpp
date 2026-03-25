#ifdef __linux__
#include "platform_linux.h"
#include "platform_interface_linux.h"
#include <GLFW/glfw3.h>
#include "glfw_window.h"
#include "render_device_factory.h"
#include "Input/input_handler_glfw.h"
#include "Debug/debug.h"
#include "GameEngine/game_engine.h"
#include <termios.h>
#include <unistd.h>

namespace Ming3D
{
    PlatformLinux::PlatformLinux()
    {
        mPlatformInterface = std::make_unique<PlatformInterfaceLinux>();
    }

    PlatformLinux::~PlatformLinux()
    {

    }

    void PlatformLinux::Initialise()
    {
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
    }

    void PlatformLinux::Update()
    {

    }

    Rendering::RenderDevice* PlatformLinux::CreateRenderDevice()
    {
        return Rendering::RenderDeviceFactory::CreateRenderDevice();
    }

    Rendering::WindowBase* PlatformLinux::CreateOSWindow()
    {
        Rendering::WindowBase* window;
        window = new Rendering::GLFWWindow();
        window->Initialise();
        return window;
    }

    Rendering::RenderWindow* PlatformLinux::CreateRenderWindow(Rendering::WindowBase* inWindow, Rendering::RenderDevice* inDevice)
    {
        return inDevice->CreateRenderWindow(inWindow);
    }

    NetSocket* PlatformLinux::CreateSocket()
    {
        return nullptr;
    }

    InputHandler* PlatformLinux::CreateInputHandler(Rendering::WindowBase* window)
    {
        return new InputHandlerGLFW(static_cast<Rendering::GLFWWindow*>(window));
    }
    
    std::string PlatformLinux::ReadConsoleLine()
    {
        char input[256];
        read(0, &input, 256);
        size_t iEnd = 0;
        while(input[iEnd] != '\n')
            iEnd++;
        return std::string(input, 0, iEnd);
    }
}
#endif
