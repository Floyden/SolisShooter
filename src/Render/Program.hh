#pragma once
#include "Defines.hh"
#include "../Math.hh"

namespace Solis
{
    
class Program 
{
public:
    ~Program();

    void LoadFrom(const String& vs, const String& fs);

    void SetUniform1f(const String& name, float value);
    void SetUniform2f(const String& name, const Vec2& value);
    void SetUniform3f(const String& name, const Vec3& value);

    void SetUniformMat4f(const String& name, const Matrix4& value);

    void SetUniform2i(const String& name, const Vec2i& value);
    uint32_t GetHandle() const { return mHandle; }

    static SPtr<Program> Create() {
        return std::make_shared<Program>();
    }
private:
    uint32_t mHandle;
};

} // namespace Solis