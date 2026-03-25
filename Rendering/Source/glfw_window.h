#ifndef MING3D_GLFW_WINDOW_H
#define MING3D_GLFW_WINDOW_H

#include "window_base.h"

struct GLFWwindow;

namespace Ming3D::Rendering
{
    class GLFWWindow : public WindowBase
    {
    private:
        GLFWwindow* mGLFWWindow = nullptr;
        unsigned int mWindowWidth = 800;
        unsigned int mWindowHeight = 600;

        static GLFWwindow* GSharedContextWindow;

    public:
        GLFWWindow();
        virtual ~GLFWWindow();

        virtual void Initialise() override;
        virtual void SetSize(unsigned int inWidth, unsigned int inHeight) override;
        virtual unsigned int GetWidth() const override { return mWindowWidth; };
        virtual unsigned int GetHeight() const override { return mWindowHeight; };
        virtual void BeginRender() override;
        virtual void EndRender() override;
        virtual void* GetOSWindowHandle() override;
        virtual void Close() override;
        virtual bool IsOpen() override;
        GLFWwindow* GetGLFWWindow() { return mGLFWWindow; }
    };
}
#endif
