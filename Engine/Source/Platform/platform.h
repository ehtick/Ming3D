#ifndef MING3D_PLATFORM_H
#define MING3D_PLATFORM_H

#include "render_device.h"
#include "window_base.h"
#include "render_window.h"
#include "Input/input_handler.h"
#include "platform_file.h"

namespace Ming3D
{
    class NetSocket;

    class Platform
    {
    public:
        PlatformFile * mPlatformFile = nullptr;

        virtual void Initialise() = 0;
        virtual void Update() = 0;

        virtual RenderDevice* CreateRenderDevice() = 0;
        virtual WindowBase* CreateOSWindow() = 0;
        virtual RenderWindow* CreateRenderWindow(WindowBase* inWindow, RenderDevice* inDevice) = 0;
        virtual NetSocket* CreateSocket() = 0;
        virtual InputHandler* CreateInputHandler() = 0;
    };
}

#endif
