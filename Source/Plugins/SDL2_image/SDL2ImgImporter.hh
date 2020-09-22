#pragma once
#include "Core/Resource.hh"
#include "Image.hh"


namespace Solis
{

class SDL2ImgImporter
{
public:
    SDL2ImgImporter();
    ~SDL2ImgImporter();
    SPtr<Image> Import(const String& path);
private:
};

} // namespace Solis