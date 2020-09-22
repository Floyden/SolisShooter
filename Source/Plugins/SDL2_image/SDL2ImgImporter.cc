#include "SDL2ImgImporter.hh"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

namespace Solis
{

SDL2ImgImporter::SDL2ImgImporter()
{
    IMG_Init(IMG_INIT_PNG);
}

SDL2ImgImporter::~SDL2ImgImporter()
{
    IMG_Quit();
}

SPtr<Image> SDL2ImgImporter::Import(const String& path)
{
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
    return std::make_shared<Image>(image->w, image->h, ImageFormat::eRGBA8, data);
}

} // namespace Solis