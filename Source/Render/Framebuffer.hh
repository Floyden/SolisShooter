#pragma once
#include "Defines.hh"
#include "RenderTexture.hh"

namespace Solis
{

static const uint32_t MAX_COLOR_ATTACHMENTS = 8;

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();

    void Bind();
    void Build();

    void BindTexture(uint32_t attachment, uint32_t texture);
    void BindTexture(uint32_t attachment, SPtr<RenderTexture> texture);
    void UnbindTexture(uint32_t attachment);

    void BindDepthbuffer(uint32_t buffer);
    void BindDepthbuffer(SPtr<RenderTexture> texture);
    void UnbindDepthbuffer(uint32_t buffer);

private:
    uint32_t mHandle;
    Array<uint32_t, MAX_COLOR_ATTACHMENTS> mBoundTextures;
    uint32_t mDepthbuffer;
};

} // namespace Solis
