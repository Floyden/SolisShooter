#pragma once
#include "Defines.hh"

namespace Solis
{

enum class RenderTextureFormat
{
    R8,
    RG8,
    RGB8,
    RGBA8,
    RGB10A2,
    D32,
    D24S8,
};

class RenderTexture
{
public:
    RenderTexture(uint32_t width, uint32_t height, RenderTextureFormat fmt);
    ~RenderTexture();

    uint32_t GetHandle() const 
    {
        return mHandle;
    }

    static uint32_t GetGLInternalFormat(RenderTextureFormat format);
    static uint32_t GetGLFormat(RenderTextureFormat format);
    static uint32_t GetGLDataType(RenderTextureFormat format);


private:
    uint32_t mHandle;
    uint32_t mWidth;
    uint32_t mHeight;

    RenderTextureFormat mFormat;
};
    
} // namespace Solis
