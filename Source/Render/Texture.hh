#pragma once
#include "Defines.hh"
#include "Core/ResourceHandle.hh"
#include "Core/Resource.hh"
#include "Image.hh"

namespace Solis
{

class Texture;
using HTexture = ResourceHandle<Texture>;

class Texture : public Resource {
public:
    ~Texture();
    static HTexture Create(SPtr<Image> image);

    uint32_t GetHandle() const { return mHandle; }
private:
    uint32_t mHandle;
};


} // namespace Solis