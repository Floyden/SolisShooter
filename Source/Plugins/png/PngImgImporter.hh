#pragma once
#include "Core/Resource.hh"
#include "Image.hh"

namespace Solis
{

class PngImgImporter
{
public:
    PngImgImporter();
    ~PngImgImporter();
    SPtr<Image> Import(const String& path);
private:
};

} // namespace Solis