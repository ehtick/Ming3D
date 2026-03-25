#include "glfw_window.h"
#include <GLFW/glfw3.h>
#include "Debug/st_assert.h"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#elif defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#endif

namespace Ming3D::Rendering
{
    GLFWwindow* GLFWWindow::GSharedContextWindow = nullptr;

    GLFWWindow::GLFWWindow()
    {

    }

    GLFWWindow::~GLFWWindow()
    {
        if (mGLFWWindow != nullptr)
        {
            glfwDestroyWindow(mGLFWWindow);
            mGLFWWindow = nullptr;
        }
    }

    void GLFWWindow::Initialise()
    {
        if (mGLFWWindow == nullptr)
            mGLFWWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "Ming3D", nullptr, GSharedContextWindow);

        __Assert(mGLFWWindow != nullptr);

        if (GSharedContextWindow == nullptr)
            GSharedContextWindow = mGLFWWindow;

        glfwMakeContextCurrent(mGLFWWindow);
        glfwSwapInterval(1); // vsync
    }

    void GLFWWindow::SetSize(unsigned int inWidth, unsigned int inHeight)
    {
        mWindowWidth = inWidth;
        mWindowHeight = inHeight;

        if (mGLFWWindow != nullptr)
            glfwSetWindowSize(mGLFWWindow, mWindowWidth, mWindowHeight);
    }

    void GLFWWindow::BeginRender()
    {
        glfwMakeContextCurrent(mGLFWWindow);
    }

    void GLFWWindow::EndRender()
    {
        glfwSwapBuffers(mGLFWWindow);
    }

    void* GLFWWindow::GetOSWindowHandle()
    {
#ifdef _WIN32
        return glfwGetWin32Window(mGLFWWindow);
#elif defined(__linux__)
        return reinterpret_cast<void*>(glfwGetX11Window(mGLFWWindow));
#else
        return nullptr;
#endif
    }

    void GLFWWindow::Close()
    {
        glfwDestroyWindow(mGLFWWindow);
        mGLFWWindow = nullptr;
    }

    bool GLFWWindow::IsOpen()
    {
        return mGLFWWindow != nullptr;
    }
}
