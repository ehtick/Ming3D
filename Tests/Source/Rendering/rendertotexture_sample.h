#pragma once

#include "glm/glm.hpp"
#include <vector>


#include "render_device.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader_program.h"

#include "sample_base.h"

namespace Ming3D
{
    class RenderToTextureSample : public SampleBase
    {
    private:
        std::vector<ModelData*> mModels;

        Rendering::RenderTarget* mRenderTarget;
        Rendering::RenderTarget* mTextureRenderTarget;
        Rendering::RasteriserState* mOrthoRasterState;

    protected:
        virtual void init() override;
        virtual void tick() override;
    };
}
