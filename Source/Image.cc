#include "Image.hh"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>

SPtr<Image> Image::FromFile(const String& path) {
    auto res = std::make_shared<Image>();

    auto image = IMG_Load(path.c_str());

    if(!image) {
        std::cout << IMG_GetError();
        return nullptr;
    }

    res->mHeight = image->h;
    res->mWidth = image->w;
    //auto size = image->h * image->w * image->format->BytesPerPixel;
    
    SDL_LockSurface(image);

    res->mData.clear();
    for (int i = 0; i < image->h; i++)
    {
        res->mData.insert(res->mData.end(), 
            &reinterpret_cast<char*>(image->pixels)[i * image->pitch], 
            &reinterpret_cast<char*>(image->pixels)[i * image->pitch + image->pitch]);
    }
        
    SDL_UnlockSurface(image);

    SDL_FreeSurface(image);
    return res;
}