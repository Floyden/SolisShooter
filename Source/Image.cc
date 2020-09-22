#include "Image.hh"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <algorithm>
#include <bits/stdint-uintn.h>
#include <iostream>

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

SPtr<Image> Image::FromFile(const String& path) {

    auto image = IMG_Load(path.c_str());

    if(!image) {
        std::cout << IMG_GetError();
        return nullptr;
    }

    
    SDL_LockSurface(image);

    Vector<uint8_t> data;
    for (int i = 0; i < image->h; i++)
    {
        data.insert(data.end(), 
            &reinterpret_cast<char*>(image->pixels)[i * image->pitch], 
            &reinterpret_cast<char*>(image->pixels)[i * image->pitch + image->pitch]);
    }
        
    SDL_UnlockSurface(image);

    SDL_FreeSurface(image);
    auto res = std::make_shared<Image>(image->w, image->h, ImageFormat::eRGBA8, data);
    return res;
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