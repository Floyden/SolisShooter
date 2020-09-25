#include "Image.hh"
#include <algorithm>
#include <iostream>

namespace Solis
{
    
Image::Image(uint32_t width, uint32_t height, ImageFormat format) 
{
    int size = GetDstImageSize(width, height, format);

    mData.resize(size);

    mWidth = width;
    mHeight = height;
    mFormat = format;
}

Image::Image(uint32_t width, uint32_t height, ImageFormat format, const Vector<uint8_t>& data) 
{
    size_t size = GetDstImageSize(width, height, format);

    if(data.size() != static_cast<size_t>(size)) {
        std::cout << "Image: unexpected data size of: " << data.size() << ", expected: " << size << std::endl;
        return;
    }

    mWidth = width;
    mHeight = height;
    mFormat = format;
    mData = data;
}

int Image::GetDstImageSize(uint32_t width, uint32_t height, ImageFormat format)
{
    // I can imagine that this gets more complicated with the addition of mipmaps and other formats
    int pixelSize = GetFormatPixelSize(format);
    int size = width * height * pixelSize;

    return size;
}

int Image::GetFormatPixelSize(ImageFormat format)
{
    switch (format) {
        case ImageFormat::eR8:
            return 1;
        case ImageFormat::eRG8:
            return 2;
        case ImageFormat::eRGB8:
            return 3;
        case ImageFormat::eRGBA8:
            return 4;
        case ImageFormat::eRF:
            return 4;
        case ImageFormat::eRGF:
            return 8;
        case ImageFormat::eRGBF:
            return 12;
        case ImageFormat::eRGBAF:
            return 16;
    }
    return 0;
}

} // namespace Solis