#pragma once
#include "Core/Resource.hh"
#include <bits/stdint-uintn.h>

enum class ImageFormat
{
    eR8,
    eRG8,
    eRGB8,
    eRGBA8,
    eRF, // Float values
    eRGF,
    eRGBF,
    eRGBAF,
};

class Image : public Resource {
public:
    static SPtr<Image> FromFile(const String& path);

    /// Create an empty Image
    Image() {};
    /// Create an image with given size and format
    Image(uint32_t width, uint32_t height, ImageFormat format);
    /// Create an image with given size, format and data
    Image(uint32_t width, uint32_t height, ImageFormat format, const Vector<uint8_t>& data);

    uint32_t GetWidth() const { return mWidth; }
    uint32_t GetHeight() const { return mHeight; }
    uint32_t GetSize() const { return mData.size(); }
    const Vector<uint8_t>& GetData() const { return mData; }

    static int GetFormatPixelSize(ImageFormat format);
    static int GetDstImageSize(uint32_t width, uint32_t height, ImageFormat format);
private:
    Vector<uint8_t> mData;
    uint32_t mWidth;
    uint32_t mHeight;
    ImageFormat mFormat;
};