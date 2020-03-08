#ifndef MING3D_CAMERA_H
#define MING3D_CAMERA_H

#include "glm/glm.hpp"

namespace Ming3D
{
    class RenderPipelineParams;

    namespace Rendering
    {
        class RenderTarget;
    }

    class Camera
    {
    public:
        Camera();
        ~Camera();

        glm::mat4 mCameraMatrix;
        Rendering::RenderTarget* mRenderTarget = nullptr;
        RenderPipelineParams* mRenderPipelineParams = nullptr;
    };
}

#endif
