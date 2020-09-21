#pragma once
#include "Defines.hh"

class Image {
public:
    static SPtr<Image> FromFile(const String& path);

    uint32_t GetWidth() const { return mWidth; }
    uint32_t GetHeight() const { return mHeight; }
    uint32_t GetSize() const { return mData.size(); }
    const char* GetData() const { return mData.data(); }
private:
    Vector<char> mData;
    uint32_t mWidth;
    uint32_t mHeight;
};