#ifdef MING3D_D3D11
#include "constant_buffer_d3d11.h"

namespace Ming3D::Rendering
{
    ConstantBufferD3D11::~ConstantBufferD3D11()
    {
        if (mConstantData != nullptr)
        {
            delete mConstantData;
        }
    }
}
#endif
