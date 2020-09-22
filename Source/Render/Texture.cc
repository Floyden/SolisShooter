#include "Texture.hh"
#include <GL/glew.h>

namespace Solis
{

SPtr<Texture> Texture::Create(SPtr<Image> image)
{
    auto res = std::make_shared<Texture>();

    glGenTextures(1, &res->mHandle);
    glBindTexture(GL_TEXTURE_2D, res->mHandle);

    if(image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->GetWidth(), image->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetData().data());
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return res;
}

Texture::~Texture()
{
    glDeleteTextures(1, &mHandle);
}

} // namespace Solis