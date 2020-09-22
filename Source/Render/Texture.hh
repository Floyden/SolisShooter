#pragma once
#include "Defines.hh"
#include "Image.hh"

namespace Solis
{

class Texture {
public:
    ~Texture();
    static SPtr<Texture> Create(SPtr<Image> image);

    uint32_t GetHandle() const { return mHandle; }
private:
    uint32_t mHandle;
};

} // namespace Solis